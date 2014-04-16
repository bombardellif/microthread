/* 
 * File:   mmutex_t.h
 * Author: william
 *
 * Created on April 16, 2014, 2:04 PM
 */

#ifndef MMUTEX_T_H
#define	MMUTEX_T_H

#include "OrderedQueue.h"

typedef struct Smmutex_t{
    int flag;
    OrderedQueue waitingQueue;
} mmutex_t;

mmutex_t* newmmutex_t(mmutex_t* mutex);
void setFlag(mmutex_t* mutex, MutexFlag flag);
void addToWaitingQueue(mmutex_t* mutex, uth_tid* th);
MutexFlag getFlag(mmutex_t* mutex);
uth_tid* getFromWaitingQueue(mmutex_t* mutex);

#endif	/* MMUTEX_T_H */

