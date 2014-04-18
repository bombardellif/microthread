/* 
 * File:   List.h
 * Author: william
 *
 * Created on April 15, 2014, 11:49 PM
 */

#ifndef LIST_H
#define	LIST_H

#include "mdata.h"

List* newList(List* listDescriber);
void freeList(List* listDescriber);
void listCheckRep(List* listDescriber);
void listAdd(List* listDescriber, void* e, int (*comparator) (void*, void*));
void listAppend(List* listDescriber, void* e);
void* listGet(List* listDescriber, void* e, int (*comparator) (void*, void*));
void listRemove(List* listDescriber, void* e, int (*comparator) (void*, void*));

#endif	/* LIST_H */

