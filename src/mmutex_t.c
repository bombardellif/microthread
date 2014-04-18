/* 
 * File:   OrderedQuee.c
 * Author: william
 *
 * Created on April 16, 2014, 13:25 PM
 */

#include "mmutex_t.h"
#include <assert.h>

mmutex_t* newmmutex_t(mmutex_t* mutex){
    mutex = (mmutex_t*)malloc(sizeof(mmutex_t));
    mutex->flag = MutexFlag.Free;
    newOrderedQueue(mutex->waitingQueue);
    return mutex;
}

void setFlag(mmutex_t* mutex, MutexFlag flag){
    assert(mutex != NULL);
    
    mutex->flag = flag;
}

void addToWaitingQueue(mmutex_t* mutex, uth_id* th){
    assert(mutex != NULL);
    
    enqueue(mutex->waitingQueue, th, intPointerCompare);
}

MutexFlag getFlag(mmutex_t* mutex){
    return mutex->flag;
}

uth_id* getFromWaitingQueue(mmutex_t* mutex){
    return (uth_id*)dequeue(mutex->waitingQueue);
}
