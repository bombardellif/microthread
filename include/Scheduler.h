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
void schedule();
void addThread(Tcb* tcb);
void saveContext();
void changeState(State state, Tcb* tcb);
Tcb* getThreadById(uth_id th);
ucontext_t* getTerminateContext();
Tcb* getExecutingThread();

#endif	/* SCHEDULER_H */

