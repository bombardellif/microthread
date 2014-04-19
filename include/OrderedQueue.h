/* 
 * File:   OrderedQueue.h
 * Author: william
 *
 * Created on April 16, 2014, 12:43 PM
 */

#ifndef ORDEREDQUEUE_H
#define	ORDEREDQUEUE_H

#include "mdata.h"

OrderedQueue* newOrderedQueue(OrderedQueue* queue);
void freeOrderedQueue(OrderedQueue* queue);
boolean orderedQueueEmpty(OrderedQueue* queue);
void orderedQueueEnqueue(OrderedQueue* queue, void* e, int (*comparator) (void*, void*));
void* orderedQueueDequeue(OrderedQueue* queue);

#endif	/* ORDEREDQUEUE_H */

