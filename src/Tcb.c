/* 
 * File:   tcb.c
 * Author: fernando
 *
 * Created on 15. April 2014, 23:28
 */

#include "Tcb.h"

#include <stdlib.h>

Tcb* createTcb(uth_id id, ucontext_t context) {
    Tcb *newTcb;
    
    newTcb = (Tcb*)malloc(sizeof(Tcb));
    
    newTcb->id = id;
    newTcb->context = context;
    
    return newTcb;
}

void freeTcb(Tcb* tcb) {
    free(tcb);
}

