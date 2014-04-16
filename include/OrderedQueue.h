/* 
 * File:   OrderedQueue.h
 * Author: william
 *
 * Created on April 16, 2014, 12:43 PM
 */

#ifndef ORDEREDQUEUE_H
#define	ORDEREDQUEUE_H

//Extends List
#include "List.h"

typedef List OrderedQueue;

OrderedQueue* newOrderedQueue(OrderedQueue* queue);
void* enqueue(OrderedQueue* queue, void* e, int (*comparator) (void*, void*));
void* dequeue(OrderedQueue* queue);

#endif	/* ORDEREDQUEUE_H */

