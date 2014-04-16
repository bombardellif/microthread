/* 
 * File:   List.h
 * Author: william
 *
 * Created on April 15, 2014, 11:49 PM
 */

#ifndef LIST_H
#define	LIST_H

#include <stdlib.h>

typedef struct SListDesc{
    ListElem *begin;
    ListElem *end;
} List;

typedef struct SListElem{
    void *e;
    ListElem *prev;
    ListElem *next;
} ListElem;

List* newList(List* listDescriber);
void add(List* listDescriber, void* e);
void* get(List* listDescriber, void* e, int (*comparator) (void*, void*));
void remove(List* listDescriber, void* e, int (*comparator) (void*, void*));

#endif	/* LIST_H */

