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
