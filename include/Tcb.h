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
    int id;
    int waitingThId;
    ucontext_t context;
    unsigned long executedTime;
    struct timespec initialTime;
} Tcb;

int tcbCompare(Tcb* a, Tcb* b);
int executedTimeTcbCompare(Tcb* a, Tcb* b);
Tcb* createTcb(int id, ucontext_t context);
void freeTcb(Tcb* tcb);

#endif	/* TCB_H */

