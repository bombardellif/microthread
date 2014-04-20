/* 
 * File:   main.c
 * Author: william
 *
 * Created on April 18, 2014, 10:02 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"
#include "OrderedQueue.h"
#include "mmutex_t.h"
#include "mthread.h"


void testList(){
    
    List* listDescriber = newList();
    printf("%p\n",listDescriber);
    listCheckRep(listDescriber);
    printf("-");
    
    int *e = malloc(sizeof(int));
    *e = 1;
    listAdd(listDescriber, e, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");

    int *f = malloc(sizeof(int));
    *f = 3;
    listAdd(listDescriber, f, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");

    int *g = malloc(sizeof(int));
    *g = 0;
    listAdd(listDescriber, g, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-\n");
    
    assert((listGet(listDescriber, f, (int(*)(void*,void*))intPointerCompare) == f));
    listCheckRep(listDescriber);
    printf("-");
    
    int *h = malloc(sizeof(int));
    *h = 2;
    listAdd(listDescriber, h, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    int *i = malloc(sizeof(int));
    *i = 0;
    listAppend(listDescriber, i);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((*((int*)listGet(listDescriber, i, (int(*)(void*,void*))intPointerCompare))) == *i);    
    listCheckRep(listDescriber);
    printf("-\n");
    
    listRemove(listDescriber, i, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    
    int *j = malloc(sizeof(int));
    *j = 100;
    listAppend(listDescriber, j);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((listGet(listDescriber, h, (int(*)(void*,void*))intPointerCompare) == h));
    listCheckRep(listDescriber);
    printf("-\n");
    
    listRemove(listDescriber, h, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((*((int*)listGet(listDescriber, g, (int(*)(void*,void*))intPointerCompare))) == *g);
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, g, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    printf("%p", listGet(listDescriber, i, (int(*)(void*,void*))intPointerCompare));
    assert((listGet(listDescriber, i, (int(*)(void*,void*))intPointerCompare) == NULL));
    listCheckRep(listDescriber);
    printf("-");
    
    assert((listGet(listDescriber, e, (int(*)(void*,void*))intPointerCompare) == e));
    listCheckRep(listDescriber);
    printf("-\n");
    
    listRemove(listDescriber, e, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    int *k = malloc(sizeof(int));
    *k = 0;
    listAppend(listDescriber, k);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((listGet(listDescriber, f, (int(*)(void*,void*))intPointerCompare) == f));
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, f, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-\n");
    
    assert((listGet(listDescriber, k, (int(*)(void*,void*))intPointerCompare) == k));
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, k, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, j, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-\n\n");
    
    //empty
    assert(listDescriber->begin == NULL);
    assert(listDescriber->end == NULL);
    
    int *l = malloc(sizeof(int));
    *l = 3;
    listAdd(listDescriber, l, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    int *m = malloc(sizeof(int));
    *m = 2;
    listAdd(listDescriber, m, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    int *n = malloc(sizeof(int));
    *n = 1;
    listAdd(listDescriber, n, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((listGet(listDescriber, m, (int(*)(void*,void*))intPointerCompare) == m));
    listCheckRep(listDescriber);
    printf("-\n");
    
    assert((listGet(listDescriber, n, (int(*)(void*,void*))intPointerCompare) == n));
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, n, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((listGet(listDescriber, l, (int(*)(void*,void*))intPointerCompare) == l));
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, l, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-\n");
    
    assert((listGet(listDescriber, m, (int(*)(void*,void*))intPointerCompare) == m));
    listCheckRep(listDescriber);
    printf("-");
    
    listRemove(listDescriber, m, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(listDescriber);
    printf("-");
    
    assert((listGet(listDescriber, m, (int(*)(void*,void*))intPointerCompare) == NULL));
    listCheckRep(listDescriber);
    printf("-");
    
    //empty
    assert(listDescriber->begin == NULL);
    assert(listDescriber->end == NULL);
}

void testOrderedQueue(){
    OrderedQueue* queue = newOrderedQueue();
    printf("%p\n",queue);
    listCheckRep(queue);
    printf("-");
    
    int* a = malloc(sizeof(int)); *a = 10;
    orderedQueueEnqueue(queue, a, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(queue);
    printf("-");
    
    int* b = malloc(sizeof(int)); *b = 20;
    orderedQueueEnqueue(queue, b, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(queue);
    printf("-");
    
    int* c = malloc(sizeof(int)); *c = 15;
    orderedQueueEnqueue(queue, c, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(queue);
    printf("-\n");
    
    assert(orderedQueueDequeue(queue) == a);
    listCheckRep(queue);
    printf("-");
    
    assert(orderedQueueDequeue(queue) == c);
    listCheckRep(queue);
    printf("-");
    
    int* d = malloc(sizeof(int)); *d = 3;
    orderedQueueEnqueue(queue, d, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(queue);
    printf("-");
    
    assert(orderedQueueDequeue(queue) == d);
    listCheckRep(queue);
    printf("-\n");
    
    assert(orderedQueueDequeue(queue) == b);
    listCheckRep(queue);
    printf("-");
    
    //empty
    assert(queue->begin == NULL);
    assert(queue->end == NULL);
    assert(orderedQueueDequeue(queue) == NULL);
    listCheckRep(queue);
    printf("-");
    
    int* e = malloc(sizeof(int)); *e = 4;
    orderedQueueEnqueue(queue, e, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(queue);
    printf("-");
    
    int* f = malloc(sizeof(int)); *f = 5;
    orderedQueueEnqueue(queue, f, (int(*)(void*,void*))intPointerCompare);
    listCheckRep(queue);
    printf("-\n");
    
    
    assert(orderedQueueDequeue(queue) == e);
    listCheckRep(queue);
    printf("-");
    
    assert(orderedQueueDequeue(queue) == f);
    listCheckRep(queue);
    printf("-");
    
    assert(queue->begin == NULL);
    assert(queue->end == NULL);
    assert(orderedQueueDequeue(queue) == NULL);
    listCheckRep(queue);
    printf("-");
}

void fun0(int* arg){
    int i;
    for(i=0;i < *arg; i++){
        //for(j=0;j<1000; j++);
        printf("fun0: %d\n",i);
        if (i%5 == 0)
            myield();
    }
    return;
}

void fun1(int* arg){
    int i;
    for(i=0;i < *arg; i++){
        //for(j=0;j<1000; j++);
        printf("fun1: %d\n",i);
        if (i%5 == 0)
            myield();
    }
    return;
}

void fun2(int* arg){
    int i;
    for(i=0;i < *arg; i++){
        //for(j=0;j<100; j++);
        printf("fun2: %d\n",i);
        if (i%5 == 0)
            myield();
    }
    return;
}

void testMthread(){
    int *arg0 = (int*)malloc(sizeof(int));
    int *arg1 = (int*)malloc(sizeof(int));
    int *arg2 = (int*)malloc(sizeof(int));;
    *arg0 = 10; *arg1 = 20; *arg2 = 30;
    int id0, id1, id2, i;
    
    id0 = mcreate((void (*)(void*))fun0, (void*)arg0);
    id1 = mcreate((void (*)(void*))fun1, (void*)arg1);
    
    printf("main: fun0 and fun1 created\n");
    
    myield();
    
    for(i = 0; i<10; i++){
        printf("main: %d\n",i);
        if (i % 5 == 0)
            myield();
    }
    
    mjoin(id0);
    
    id2 = mcreate((void (*)(void*))fun2, (void*)arg2);
    printf("main: fun2 created\n");
    myield();
    
    for(i = 0; i<10; i++){
        printf("main2: %d\n",i);
        if (i % 5 == 0)
            myield();
    }
    
    mjoin(id1);
    mjoin(id2);
    
    printf("main: finish");

}

void fun10(){
    int i,j;
    for(i = 0; i<50; i++){
        for (j = 0; j<500; j++);
        printf("fun10: %d\n",i);
        if (i % 5 == 0)
            myield();
    }
}

void fun12(int* arg){
    printf("fun12: hello\n");
    if (arg != NULL)
        mjoin(*arg);
    printf("fun12: bye\n");
}

void fun11(int *arg){
    int i;
    int id1;
    
    id1 = mcreate((void (*)(void*))fun12, arg);
    printf("fun11: fun12 created\n");
    mjoin(id1); //deadlock
    
    for(i = 0; i<10; i++){
        printf("fun11: %d\n",i);
        if (i % 5 == 0)
            myield();
    }
}

void testMthread2(){
    void *arg = NULL;
    int id1, id2, i;
    
    //This have to work without crashing
    myield();
    myield();
    
    //Simple Test with one single thread
    mcreate((void (*)(void*))fun10, NULL);
    printf("\nmain: fun10 create\n");
    myield();
    
    //Just add on more thread
    id1 = mcreate((void (*)(void*))fun10, arg);
    printf("main: fun10 created\n");
    
    //Test Interdependency, fun11 waits for fun12, that waits for fun11 (deadlock)
    //fun11 prints shall never be executed
    id2 = id1+1;
    id2 = mcreate((void (*)(void*))fun11, &id2);
    printf("main: fun11 created\n");
    myield();
    
    //fun12 will require join from fun10
    mcreate((void (*)(void*))fun12, &id1);
    printf("main: fun12 created[2]\n");
    myield();
    
    for (i=0;i<1000;i++);
    printf("main: test assert\n");
    //Once fun12 is waiting for fun10, this might return -1
    //This actually depends ont the time fun10 takes to execute, so we may manipulate this to observe results
    assert(mjoin(id1) == -1);
    
    assert(mjoin(10) == -1); //Obvious error
    
    printf("main: finish"); //Didn't crash, that's okay

}

void testMthread3(){
    int id0, id1;
    
    //fun12 will require join from main thread
    id0 = 0;
    id1 = mcreate((void (*)(void*))fun12, &id0);
    printf("main: fun12 created[1]\n");
    myield();
    mjoin(id1);
    //Nothing more executes from here
    
    printf("main: finish"); //Didn't crash, that's okay

}

int main(int argc, char** argv) {
    testList();
    printf("\n____\n");
    testOrderedQueue();
    printf("\n____\n");
    testMthread();
    printf("\n____\n");
    testMthread2();
    printf("\n____\n");
    //testMthread3(); //Uncomment this to see a deadlock error
    return 0;
}

