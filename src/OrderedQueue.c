/* 
 * File:   OrderedQuee.c
 * Author: william
 *
 * Created on April 16, 2014, 13:25 PM
 */

#include "OrderedQueue.h"


OrderedQueue* newOrderedQueue(OrderedQueue* queue){
    queue = NULL;
    return queue;
}

void enqueue(OrderedQueue* queue, void* e, int (*comparator) (void*, void*)){
    add(queue, e, comparator);
}

void* dequeue(OrderedQueue* queue){
    ListElem *removing;
    
    if (queue != NULL && queue.begin != NULL){
        removing = queue.begin;
        //Rearrange pointers
        queue.begin = queue.begin->next;
               
        //if we just removed the only element
        if (queue.begin == NULL)
            queue = queue.end = NULL;
        else
            queue.begin->prev = NULL;
        
        return removing;
    }else{
        return NULL;
    }
}

