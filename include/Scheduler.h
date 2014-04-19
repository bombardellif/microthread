/* 
 * File:   Scheduler.h
 * Author: fernando
 *
 * Created on 15. April 2014, 23:51
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "mdata.h"
#include "Tcb.h"
#include <ucontext.h>

typedef enum {Ready, Waiting, Running} State;

void setYielding(boolean yield);
void schedule(void);
void addThread(Tcb* tcb);
void saveContext(void);
void changeStateToReady(Tcb* tcbToChange);
boolean changeStateToWaiting(Tcb* tcbToDepend);
Tcb* getThreadById(int th);
ucontext_t* getTerminateContext(void);
void terminateThread(void);
Tcb* getExecutingThread(void);
void initialize(void);
unsigned long calculateExecuteTime(Tcb* thread);


#endif	/* SCHEDULER_H */

