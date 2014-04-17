/* 
 * File:   tcb.c
 * Author: fernando
 *
 * Created on 15. April 2014, 23:28
 */

#include "Tcb.h"

#include <stdlib.h>


/**
 * Compare two Tcb pointers, returns 0 iff the field id of the struct pointed by a is equal (natural comparison) to the one pointed by b, returns 1 iff the field id of a is greater than the id of b, returns -1 iff the id of a is less than the id of b.
 * @param a First argument to be compared
 * @param b Second argument to be compared
 * @return Semantically speaking, returns 0 iff both threads are the same, 1 iff the id of a > b, -1 otherwise
 */
int tcbCompare(Tcb* a, Tcb* b){
    return (a->id == b->id) ? 0 : ((a->id > b->id) ? 1 : -1);
}

Tcb* createTcb(uth_id id, ucontext_t context) {
    Tcb *newTcb;
    
    newTcb = (Tcb*)malloc(sizeof(Tcb));
    
    newTcb->id = id;
    newTcb->context = context;
    newTcb->waitingThId = NULL;
    newTcb->executedTime = 0;
    
    return newTcb;
}

void freeTcb(Tcb* tcb) {
    free(tcb);
}

