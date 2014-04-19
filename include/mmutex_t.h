/* 
 * File:   mmutex_t.h
 * Author: william
 *
 * Created on April 16, 2014, 2:04 PM
 */

#ifndef MMUTEX_T_H
#define	MMUTEX_T_H

#include "OrderedQueue.h"
#include "mdata.h"

typedef enum {Locked, Free} MutexFlag;


mmutex_t* newmmutex_t(mmutex_t* mutex);
void setFlag(mmutex_t* mutex, MutexFlag flag);
void addToWaitingQueue(mmutex_t* mutex, int* th);
MutexFlag getFlag(mmutex_t* mutex);
int* getFromWaitingQueue(mmutex_t* mutex);
int intPointerCompare(int* a, int* b);

#endif	/* MMUTEX_T_H */

