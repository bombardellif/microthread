/* 
 * File:   List.c
 * Author: william
 *
 * Created on April 16, 2014, 00:13 AM
 */

#include <stdlib.h>
#include <assert.h>
#include "List.h"

List* newList(){
    List* listDescriber = (List*)malloc(sizeof(List));
    listDescriber->begin = NULL;
    listDescriber->end = NULL;
    return listDescriber;
}

void freeList(List* listDescriber){
    free(listDescriber);
    listDescriber = NULL;
}

void listCheckRep(List* listDescriber){
    assert(listDescriber);
    assert(listDescriber->begin == NULL ? listDescriber->end == NULL : TRUE);
    
    if (listDescriber->begin){
        int size = 0;
        //Iterate over the list, counting
        ListElem *current = listDescriber->begin;
        while(current != NULL){
            size++;
            //move forward
            current = current->next;
        }
        
        if (size == 0){
            assert(listDescriber->begin == NULL);
            assert(listDescriber->end == NULL);
        }else{
            if (size == 1)
                assert(listDescriber->begin == listDescriber->end);
            else{
                if (size==2){
                    assert(listDescriber->begin->next == listDescriber->end);
                    assert(listDescriber->end->prev == listDescriber->begin);
                }
                assert(listDescriber->begin->next);
                assert(listDescriber->end->prev);
            }
            assert(listDescriber->begin->prev == NULL);
            assert(listDescriber->end->next == NULL);
        }
    }
}

void listAdd(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    //Crete new element of the list
    ListElem *newOne = (ListElem*)malloc(sizeof(ListElem));
    
    assert(newOne != NULL);
    assert(listDescriber != NULL);
    assert(e != NULL);
    assert(comparator != NULL);
    
    newOne->e = e;
    
    //If the list is empty
    if (listDescriber->begin == NULL){
        
        assert(listDescriber->end == NULL);
        
        //Then, first initialize it
        listDescriber->begin = newOne;
        listDescriber->end   = newOne;
        //new one is the first, hence the previous is null
        newOne->prev = NULL;
        newOne->next = NULL;
    }else{
        //Iterate over the list, searching
        ListElem *current = listDescriber->begin;
        while(current != NULL){
            //Comparator returns greater than 0 iff current->e is greater than e
            if ((*comparator)(current->e, e) > 0){
                break;
            }
            //move forward
            current = current->next;
        }

        //Surfed the whole list, so insert in the end
        if (current == NULL){
            assert(listDescriber->end != NULL);
            //Put pointers in order, note we add the new one to the end
            listDescriber->end->next = newOne;
            newOne->prev = listDescriber->end;
            listDescriber->end = newOne;
            newOne->next = NULL;

        }else{ //Found a place inside the list to insert e

            //newOne will be inserted just before current
            newOne->next = current;
            newOne->prev = current->prev;
            current->prev = newOne;

            //Inserting in the first position?
            if (listDescriber->begin == current){
                listDescriber->begin = newOne;
                newOne->prev = NULL;
            }else{
                assert(newOne->prev != NULL);
                newOne->prev->next = newOne;
            }
        }
    }
    return;
}

void listAppend(List* listDescriber, void* e){
    //Crete new element of the list
    ListElem *newOne = (ListElem*)malloc(sizeof(ListElem));
    
    assert(newOne != NULL);
    assert(listDescriber != NULL);
    assert(e != NULL);
    
    newOne->e = e;
    
    //If the list is empty
    if (listDescriber->begin == NULL){
        
        assert(listDescriber->end == NULL);
        
        //Then, first initialize it
        listDescriber->begin = newOne;
        listDescriber->end   = newOne;
        //new one is the first, hence the previous is null
        newOne->prev = NULL;
    }else{
        assert(listDescriber->end != NULL);
        
        //Put pointers in order, note we add the new one to the end
        listDescriber->end->next = newOne;
        newOne->prev = listDescriber->end;
        listDescriber->end = newOne;
        newOne->next = NULL;
    }
    
    newOne->next = NULL;
    
    return;
}

void* listGetElement(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    assert(listDescriber != NULL);
    assert(e != NULL);
    assert(comparator != NULL);
    
    //If the list is empty
    if (listDescriber->begin == NULL){
        assert(listDescriber->end == NULL);
        return NULL;
    }else{
        //Iterate over the list, searching
        ListElem *current = listDescriber->begin;
        while(current != NULL){
            //Comparator returns 0 iff e is equals to current->e
            if (!(*comparator)(e, current->e)){
                return current;
            }
            //move forward
            current = current->next;
        }
        //Surfed the whole list, didn't find
        return NULL;
    }
    
}

void* listGet(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    assert(listDescriber != NULL);
    assert(e != NULL);
    assert(comparator != NULL);
    
    ListElem *el;
    //Look for the target element
    if ((el = listGetElement(listDescriber, e, comparator)) != NULL){
        //If found return just the important data
        return el->e;
    }else{
        return NULL;
    }
}

void listRemove(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    assert(listDescriber != NULL);
    assert(e != NULL);
    assert(comparator != NULL);
    
    ListElem *removing;
    //If we have found the one we want to remove
    if ((removing = listGetElement(listDescriber, e, comparator)) != NULL){
        //If we remove the first
        if (removing->prev == NULL)
            listDescriber->begin = removing->next; //Change the begin
        else
            removing->prev->next = removing->next; //Else, just rearrange pointer

        //If we remove the last
        if (removing->next == NULL){
            listDescriber->end = removing->prev; //Change the end

            //If we remove the first and last (the only one in the list)
            if (removing->prev == NULL){
                listDescriber->begin = NULL; //Set describer begin to null
                assert(listDescriber->end == NULL);
            }
        }
        else
            removing->next->prev = removing->prev;

        //Finally
        free(removing);
    }
}
