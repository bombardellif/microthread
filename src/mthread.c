/* 
 * File:   mthread.c
 * Author: william
 *
 */

#include "mthread.h"
#include "mdata.h"
#include <ucontext.h>
#include <stdlib.h>
#include <assert.h>

static uth_id lastThreadId = 0;

int mcreate (void (*start_routine)(void*), void *arg){
    assert(start_routine != NULL);
    
    //Creates the context and initialize it just to get a model
    ucontext_t newContext;
    getcontext(&newContext);
    //The point in which thread will come back when it is finished
    newContext.uc_link = getTerminateContext();
    newContext.uc_stack.ss_sp = malloc(SIGSTKSZ);
    newContext.uc_stack.ss_size = SIGSTKSZ;
    
    makecontext(newContext, start_routine, 1, arg);
    
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