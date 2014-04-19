/* 
 * File:   Scheduler.c
 * Author: fernando
 *
 * Created on 15. April 2014, 23:56
 */

#include "Scheduler.h"
#include "mdata.h"
#include "Tcb.h"
#include "List.h"
#include "OrderedQueue.h"
#include <ucontext.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <assert.h>


static OrderedQueue* readyQueue = NULL;
static List* threadList = NULL;
static Tcb* executingThread = NULL;
static boolean yielding;
static ucontext_t* terminateContext;


/**
 * This function changes the state yielding of the scheduler (True or false)
 * @param yield
 */
void setYielding(boolean yield) {
    yielding = yield;
}

/**
 * Add the thread tcb to the list of current threads in the scheduler
 * @param tcb Thread Control Block related to the thread to be inserted
 */
void addThread(Tcb* tcb){
    assert(tcb != NULL);
    listAppend(threadList, tcb);
}

/**
 * Schedule processes, choose a new ready thread to run on CPU, assume that the last executed thread was succesfully taken out from the CPU and had its context and statistics saved.
 * If there is no ready thread, then exit program with failure signal
 */
void schedule(void){
    //Only schedule if scheduler is in yield state, 
    if (yielding == TRUE){    
        //Yield is false now, it means that we are about finish the scheduling. 
        //After the next thread finishes the processing maybe pass through this function, but we don't want to reschedule, therefore, set yield to false.
        setYielding(FALSE);
        
        assert(readyQueue != NULL);
        
        //No ready thread available, nothing to do
        if (orderedQueueEmpty(readyQueue)){
            fprintf(stderr, NOTHING_EXECUTE_ERRMSG);
            exit(EXIT_FAILURE);
        }
        
        //Take the next thread from the ready queue
        Tcb* nextToRun = (Tcb*)orderedQueueDequeue(readyQueue);

        //There might have come something
        assert(nextToRun != NULL);
        
        executingThread = nextToRun;
        
        clock_gettime(CLOCK_MONOTONIC, &(nextToRun->initialTime));
        
        //Call the thread. Note it will not return back here, because the thread has another context. It will return to the return context sat in its structure.
        setcontext(&(nextToRun->context));
        
    }
}

/**
 * This function saves the current context in the TCB of the executing thread.
 */
void saveContext(void) {
    // assertion
    assert(executingThread != NULL);
    
    getcontext(&(executingThread->context));
}

/**
 * Change the state of the given Thread to Ready by updating its execution time
 * history and moving it to the ready queue of the scheduler.
 * Note-1: If null is sent in the parameter, then the function changes the state
 * of the current executing thread.
 * @param tcbToChange
 */
void changeStateToReady(Tcb* tcbToChange) {
    // assertion
    assert(executingThread != NULL);
    assert(readyQueue != NULL);
    
    // calculates the total of time executing by the thread
    if (!tcbToChange) {
        executingThread->executedTime = calculateExecuteTime(executingThread);
    }

    // enqueues the thread in the ready prioriry queue, if tcbToChange is null, then
    // enqueue the TCB of the current executing thread
    orderedQueueEnqueue(readyQueue, ((tcbToChange) ? tcbToChange : executingThread), (int(*)(void*,void*))executedTimeTcbCompare);
}

/**
 * Change the state of the given Thread to Wainting by updating its execution time
 * history and binding this thread to the thread to depend upon.
 * The return is TRUE if the thread was successfully blocked, or FALSE, in the case
 * it was not possible to bind the executiing thread to the one to depend upon.
 * Note-1: If null is sent in the parameter, then the function does nothing.
 * @param tcbToDepend
 * @return boolean TRUE in case of success, FALSE otherwise.
 */
boolean changeStateToWaiting(Tcb* tcbToDepend) {
    
    if (tcbToDepend) {
        if (tcbToDepend->waitingThId == -1) {
            return FALSE;
        } else {
            assert(executingThread != NULL);
            
            // calculates the total of time executing by the thread
            executingThread->executedTime = calculateExecuteTime(executingThread);

            tcbToDepend->waitingThId = executingThread->id;
        }
    }
    
    return TRUE;
}

/**
 * Returns the Thread Control Block, stored in the current list of threads, that has the id = th, sent by paramenter. If there is no such thread, returns NULL
 * @param th Id of the thread to be searched
 * @return The pointer to the thread with id = th, returns NULL if such was not found
 */
Tcb* getThreadById(int th){
    assert(th >= 0);
    
    Tcb stubThread;
    stubThread.id = th;
    
    return (Tcb*)listGet(threadList, &stubThread,  (int(*)(void*,void*))tcbCompare);
}

/**
 * Retorna o struct do context que deve ser coloca a executar ao finalizar uma 
 * thread.
 * @return ucontext_t*  Ponteiro para o contexto a executar ao finalizar thread.
 */
ucontext_t* getTerminateContext(void) {
    ucontext_t tmpContext;
    
    // Se ainda não gerou o contexto, então o gera
    if (!terminateContext) {
        
        getcontext(&tmpContext);
        
        /* Se a variável global terminateContext tiver algum valor diferente de NULL,
         * então ela já foi atribuída, logo a execução chegou aqui por meio do fim
         * de alguma thread. Logo chama a função de terminação de thread.           */
        if (terminateContext) {
            
            // Atenção: Essa chamada abaixo não retornará, pois ela chama o scheduler,
            // que coloca outro contexto a executar sem salvar o atual (que está finalizando)
            terminateThread();
        } else {
            *terminateContext = tmpContext;
        }
    }
    
    return terminateContext;
}

/**
 * Return the executing thread's TCB.
 * @return Tcb*
 */
Tcb* getExecutingThread(void) {
    return executingThread;
}

/**
 * This is the function responsable for destroying a thread. It is called implicitly
 * when a thread (context) ends. Its duties are:
 *  Move the thread that is blocked and wainting for this one to the ready queue (if there is).
 *  Release all the resources used by this thread (remove from list, free memory)
 *  Call the scheduler to execute another thread.
 * 
 * Note: This function does not return, since the context is swaped by the scheduler
 */
void terminateThread(void) {
    Tcb stubTcb;
    Tcb* waitingThread;
    
    // assertions
    assert(executingThread != NULL);
    
    if (executingThread->waitingThId != -1) {
        // create a TCB just to search the waiting thread in the list
        stubTcb.id = executingThread->waitingThId;

        // search the waiting thread and change its state to Ready
        waitingThread = listGet(threadList, (void*)&stubTcb,  (int(*)(void*,void*))tcbCompare);
        if (!waitingThread) {
            changeStateToReady(waitingThread);
        }
    }
    
    // relese the resources of this destroying thread
    listRemove(threadList, (void*)executingThread,  (int(*)(void*,void*))tcbCompare);
    freeTcb(executingThread);
    
    schedule();
    
    // execution flow must never reach this point
    assert(FALSE);
}

/**
 * Initializes the Scheduler if it has not been yet.
 * This function does the following:
 *  Creates a TCB for the main thread with Id = 0, which must be
 *      the one executing at the moment.
 *  Creates the list of threads and the ready queue.
 *  Allocate the struct terminateContext
 */
void initialize(void) {
    if (!executingThread) {
        // Get the Context of the main thread
        ucontext_t mainContext;
        getcontext(&mainContext);
        
        Tcb* mainThread = createTcb(0, mainContext);
        
        addThread(mainThread);
        
        // Creates the list of threads
        threadList = newList();
        readyQueue = newOrderedQueue();
        
        terminateContext = (ucontext_t*)malloc(sizeof(ucontext_t));
    }
}

unsigned long calculateExecuteTime(Tcb* thread) {
    struct timespec now;
    
    if (thread->initialTime.tv_sec) {
        clock_gettime(CLOCK_MONOTONIC, &now);
        
        return (now.tv_sec - thread->initialTime.tv_sec) + (now.tv_nsec - thread->initialTime.tv_nsec);
    } else {
        return 0;
    }
}