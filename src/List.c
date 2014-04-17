/* 
 * File:   List.c
 * Author: william
 *
 * Created on April 16, 2014, 00:13 AM
 */

#include "List.h"

List* newList(List* listDescriber){
    listDescriber = NULL;
    return listDescriber;
}

void listAdd(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    //Crete new element of the list
    ListElem *newOne = malloc(sizeof(ListElem));
    newOne->e = e;
    
    //If the list hasn't been initialized yet
    if (listDescriber == NULL){
        //Then, first initialize it
        listDescriber.begin = newOne;
        listDescriber.end   = newOne;
        //new one is the first, hence the previous is null
        newOne->prev = NULL;
    }else{
        //Iterate over the list, searching
        ListElem *current = &List.begin;
        while(current != NULL){
            //Comparator returns greater than 0 iff e is greater than current->e
            if ((*comparator)(e, current->e) > 0){
                break;
            }
            //move forward
            current = current->next;
        }
        
        //Surfed the whole list, so insert in the end
        if (current == NULL){
            //Put pointers in order, note we add the new one to the end
            listDescriber.end->next = newOne;
            newOne->prev = listDescriber.end;
            
        }else{ //Found a place inside the list to insert e
            
            //newOne will be inserted just before current
            newOne->next = current;
            newOne->prev = current->prev;
            current->prev = newOne;
            
            //Inserting in the first position?
            if (listDescriber->begin == current){
                listDescriber->begin = newOne;
            }else{
                newOne->prev->next = newOne;
            }
        }
    }
    return;
}

void listAppend(List* listDescriber, void* e){
    //Crete new element of the list
    ListElem *newOne = malloc(sizeof(ListElem));
    newOne->e = e;
    
    //If the list hasn't been initialized yet
    if (listDescriber == NULL){
        //Then, first initialize it
        listDescriber.begin = newOne;
        listDescriber.end   = newOne;
        //new one is the first, hence the previous is null
        newOne->prev = NULL;
    }else{
        //Put pointers in order, note we add the new one to the end
        listDescriber.end->next = newOne;
        newOne->prev = listDescriber.end;
    }
    
    newOne->next = NULL;
    
    return;
}

void* getElement(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    //If the list hasn't been initialized yet
    if (listDescriber == NULL){
        return NULL;
    }else{
        //Iterate over the list, searching
        ListElem *current = &List.begin;
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
    ListElem el;
    //Look for the target element
    if ((el = getElement(e, comparator)) != NULL){
        //If found return just the important data
        return el->e;
    }
}

void listRemove(List* listDescriber, void* e, int (*comparator) (void*, void*)){
    ListElem removing;
    //If we have found the one we want to remove
    if ((removing = getElement(e, comparator)) != NULL){
        //If we remove the first
        if (removing->prev == NULL)
            listDescriber.begin = removing->next; //Change the begin
        else
            removing->prev->next = removing->next; //Else, just rearrange pointer

        //If we remove the last
        if (removing->next == NULL){
            listDescriber.end = removing->prev; //Change the end

            //If we remove the first and last (the only one in the list)
            if (removing->prev == NULL)
                listDescriber = NULL; //Set describer to null
        }
        else
            removing->next->prev = removing->prev;

        //Finally
        free(removing);
    }
}
