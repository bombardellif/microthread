/* 
 * File:   OrderedQuee.c
 * Author: william
 *
 * Created on April 16, 2014, 13:25 PM
 */

#include "OrderedQueue.h"
#include "mdata.h"
#include <assert.h>


OrderedQueue* newOrderedQueue(OrderedQueue* queue){
    queue = (OrderedQueue*) malloc(sizeof(OrderedQueue));
    return queue;
}

boolean OrderedQueueEmpty(OrderedQueue* queue){
    return queue->begin == NULL ? TRUE : FALSE;
}

void enqueue(OrderedQueue* queue, void* e, int (*comparator) (void*, void*)){
    listAdd(queue, e, comparator);
}

void* dequeue(OrderedQueue* queue){
    assert(queue != NULL);
    
    ListElem *removing;
    
    if (queue->begin != NULL){
        removing = queue->begin;
        //Rearrange pointers
        queue->begin = queue->begin->next;
               
        //if we just removed the only element
        if (queue->begin == NULL)
            queue->end = NULL;
        else
            queue->begin->prev = NULL;
        
        void* returnElem = removing->e;
        free(removing);
        
        return returnElem;
    }else{
        return NULL;
    }
}

