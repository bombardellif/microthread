/* 
 * File:   mthread.c
 * Author: william
 *
 */

#include "mthread.h"
#include "mdata.h"
#include "mmutex_t.h"
#include "Scheduler.h"
#include <ucontext.h>
#include <stdlib.h>
#include <assert.h>

static int lastThreadId = 0;

int mcreate (void (*start_routine)(void*), void *arg){
    assert(start_routine != NULL);
    
    //Creates the context and initialize it just to get a model
    ucontext_t newContext;
    getcontext(&newContext);
    //The point in which thread will come back when it is finished
    newContext.uc_link = getTerminateContext();
    newContext.uc_stack.ss_sp = malloc(SIGSTKSZ);
    newContext.uc_stack.ss_size = SIGSTKSZ;
    
    makecontext(&newContext, (void(*)())start_routine, 1, arg);
    
    Tcb* newThread = createTcb(lastThreadId+1, newContext);
    assert(newThread != NULL);
    
    //Success
    if (newThread != NULL){
        //Control of ids
        lastThreadId++;
        
        addThread(newThread);
        
        return lastThreadId;
    }else{
        return ERR_MCREATE;
    }
}

int myield(void) {
    
    initialize();
    
    setYielding(TRUE);
    
    changeStateToReady(NULL);
    
    saveContext();
    
    schedule();
    
    return 0;
}

int mjoin(int thr) {
    Tcb *threadToWaitFor;
    boolean successBlocking;
    
    initialize();
    
    setYielding(TRUE);
    
    // search thread by id, if found, then block the current and schedule.
    if ((threadToWaitFor = getThreadById(thr))) {
        
        successBlocking = changeStateToWaiting(threadToWaitFor);
        
        saveContext();
        
        // When the thread will be unblocked, it will continue executing HERE
        // but the scheduler won't schedule, hence this following call will do nothing
        schedule();
        
        // return 0 in case of success, or -1 otherwise
        return (successBlocking) ? 0 : -1;
    } else {
    // it wasn't possible to find thr, then return -1
    
        return -1;
    }
}

int mmutex_init(mmutex_t *mutex) {
    
    newmmutex_t(mutex);
    
    return (mutex) ? 0 : -1;
}

int mlock (mmutex_t *mutex) {
    Tcb *execThread;
    
    initialize();
    
    if (mutex) {
        if (mutex->flag == Free) {
            setFlag(mutex, Locked);
        } else {
            
            execThread = getExecutingThread();
            
            // While the thread doesn't get the lock, it will keep blocking and
            // trying again
            while (mutex->flag != Free) {
                
                setYielding(TRUE);
                
                addToWaitingQueue(mutex, &execThread->id);
                
                saveContext();
                
                schedule();
            }
        }
        
        return 0;
    }
    
    return -1;
}

int munlock (mmutex_t *mutex) {
    Tcb *targetThread;
    
    if (mutex && (mutex->flag == Locked)) {
        
        setFlag(mutex, Free);
        
        targetThread = getThreadById(*(getFromWaitingQueue(mutex)));
        
        if (targetThread) {
            
            changeStateToReady(targetThread);
            
            return 0;
        }
    }
    
    return -1;
}