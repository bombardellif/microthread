/* 
 * File:   mmutex_t.c
 * Author: william
 *
 * Created on April 16, 2014, 13:25 PM
 */

#include "mmutex_t.h"

mmutex_t* newmmutex_t(mmutex_t* mutex){
    mutex->flag = MutexFlag.Free;
    mutex->waitingQueue = NULL;
    return mutex;
}

void setFlag(mmutex_t* mutex, MutexFlag flag){
    mutex->flag = flag;
}

void addToWaitingQueue(mmutex_t* mutex, uth_id* th){
    enqueue(&mutex->waitingQueue, th, intPointerCompare);
}

MutexFlag getFlag(mmutex_t* mutex){
    return mutex->flag;
}

uth_id* getFromWaitingQueue(mmutex_t* mutex){
    return dequeue(mutex->waitingQueue);
}

/**
 * Compare two int pointers, returns 0 iff the content pointed by a is equal (natural comparison) to the content pointed by b, returns 1 iff a's content is greater than b's, returns -1 iff a's content is less than b's
 * @param a First argument to be compared
 * @param b Second argument to be compared
 * @return Semantically speaking, 0 iff a is equal to b, 1 iff a > b, -1 otherwise
 */
int intPointerCompare(int* a, int* b){
    return (*a == *b) ? 0 : ((*a > *b) ? 1 : -1);
}
