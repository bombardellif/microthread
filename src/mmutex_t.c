/* 
 * File:   OrderedQuee.c
 * Author: william
 *
 * Created on April 16, 2014, 13:25 PM
 */

#include "mmutex_t.h"

/**
 * Compare two int pointers, return 0 iff the content pointed by a is equal (natural comparision) to the content pointed by b.
 * @param a First argument to be compared
 * @param b Second argument to be compared
 * @return 0 iff *a == *b, 1 otherwise
 */
int intIsEqual(int* a, int* b){
    return !(*a == *b);
}

mmutex_t* newmmutex_t(mmutex_t* mutex){
    mutex->flag = Mutex.Free;
    mutex->waitingQueue = NULL;
    return mutex;
}

void setFlag(mmutex_t* mutex, MutexFlag flag){
    mutex->flag = flag;
}

void addToWaitingQueue(mmutex_t* mutex, uth_tid* th){
    enqueue(&mutex->waitingQueue, th, intIsEqual);
}

MutexFlag getFlag(mmutex_t* mutex){
    return mutex->flag;
}

uth_tid* getFromWaitingQueue(mmutex_t* mutex){
    return dequeue(mutex->waitingQueue);
}
