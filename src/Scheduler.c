/* 
 * File:   Scheduler.c
 * Author: fernando
 *
 * Created on 15. April 2014, 23:56
 */

#include "mdata.h"
#include "Tcb.h"
#include <ucontext.h>
#include <stdlib.h>
#include <time.h>

#include <assert.h>

static OrderedQueue readyQueue = NULL;
static List threadList = NULL;
static Tcb* executingThread = NULL;
static boolean yielding;
static ucontext_t terminateContext;


/**
 * Essa função altera o estado de yielding do escalonador (Verdadeiro ou Falso)
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
    //Initialize the list, if hasn't been yet
    if (threadList == NULL){
        newList(threadList);
    }
    add(threadList, tcb, tcbCompare);
}

/**
 * Schedule processes, choose a new ready thread to run on CPU, assume that the last executed thread was succesfully taken out from the CPU and had its context and statistics saved.
 * If there is no ready thread ...
 */
void schedule(){    
    //Only schedule if scheduler is in yield state, 
    if (yielding == TRUE){    
        //Yield is false now, it means that we are about finish the scheduling. 
        //After the next thread finishes the processing maybe pass through this function, but we don't want to reschedule, therefore, set yield to false.
        setYielding(FALSE);
        
        //No ready thread available, nothing to do
        if (readyQueue == NULL){
            executingThread = NULL;
            return;
        }
        
        //Take the next thread from the ready queue
        Tcb* nextToRun = dequeue(readyQueue);

        //There might have come something
        assert(nextToRun != NULL);

        executingThread = nextToRun;
        
        time(&(nextToRun->initialTime));
        
        //Call the thread. Note it will not return back here, because the thread has another context. It will return to the return context sat in its structure.
        setcontext(&(nextToRun->context));
        
    }
}



/**
 * Esse procedimento deve salvar o contexto atual na TCB da thread em execução.
 * 
 */
void saveContext() {
    // assertion
    assert(executingThread != NULL);
    
    getcontext(&(executingThread->context));
}

/**
 * Returns the Thread Control Block, stored in the current list of threads, that has the id = th, sent by paramenter. If there is no such thread, returns NULL
 * @param th Id of the thread to be searched
 * @return The pointer to the thread with id = th, returns NULL if such was not found
 */
Tcb* getThreadById(uth_id th){
    get(threadList, &th, intPointerCompare);
}

/**
 * Retorna o struct do context que deve ser coloca a executar ao finalizar uma 
 * thread.
 * @return ucontext_t*  Ponteiro para o contexto a executar ao finlaizar thread.
 */
ucontext_t* getTerminateContext() {
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
            terminateContext = tmpContext;
        }
    }
    
    return terminateContext;
}

/**
 * Retorna o TCB da thread em execução.
 * @return Tcb*
 */
Tcb* getExecutingThread() {
    return executingThread;
}

void terminateThread() {
    
}