/* 
 * File:   tcb.h
 * Author: fernando
 *
 * Created on 14. April 2014, 13:26
 */

#ifndef TCB_H
#define	TCB_H

#include <ucontext.h>
#include <time.h>
#include "mdata.h"

typedef struct {
    uth_id id;
    uth_id waitingThId;
    ucontext_t context;
    unsigned long executedTime;
    time_t initialTime;
} Tcb;

Tcb* createTcb(uth_id id, ucontext_t context);
int freeTcb(Tcb* tcb);

#endif	/* TCB_H */

