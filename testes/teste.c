
/*
 * Programa exemplo de teste da biblioteca microthreads
 *
 * Versão 1 - 20/03/2014
 */

#include <stdio.h>
#include "mthread.h"
#include "mmutex_t.h"
#include "Scheduler.h" /*considera que este fonte está no diretório testes (vide seção 8)*/

#include <assert.h>

mmutex_t mtx;
int i;
int t2, t3;

void func0(void *arg) {
    int i;
     /*corpo da função func0 */
    for (i=0; i< 1000; i++);
    printf("yield1");
    myield();
	
    printf("yield1");
    myield();
     return;    /*termina a execução da thread via comando C */
}

void func1(void *arg) {
    int i;
     /*corpo da função func1 */
    for (i=0; i< 100000; i++);
    printf("yield2");
    myield();
	 
    return;
}    /* termina a execução da thread ao chegar ao final da função naturalmente */

void testMutex_init() {
    mmutex_t _mtx;
    int ret;
    
    // TEST CASE 1
    ret = mmutex_init(NULL);
    assert(ret == -1);
    
    printf("\tTest Case 1 passed.\n");
    
    // TEST CASE 2
    ret = mmutex_init(&_mtx);
    assert(ret == 0);
    assert(_mtx.flag == Free);
    assert(orderedQueueEmpty(_mtx.waitingQueue));
    
    
    printf("\tTest Case 2 passed.\n");
    return;
}

void testMutex_lock_f2() {
    int ret;
    
    assert(mtx.flag == Locked);
    assert(orderedQueueEmpty(mtx.waitingQueue));
    
    ret = mlock(&mtx);
        assert(ret == 0);
        
        assert(i == 2);
        assert(mtx.flag == Locked);
        assert(*((int*)(mtx.waitingQueue->begin->e)) == t3); // T3 must be the only one in the waiting list
        assert(mtx.waitingQueue->begin->next == NULL);
        
        // yield, but no other thread shall execute, therfore the flow must return immediatelly
        i++;
        myield();
        assert(i == 3);
        
        i++;
    ret = munlock(&mtx);
    
    assert(ret == 0);
    assert(mtx.flag == Free);
    
    return;
}

void testMutex_lock_f3() {
    int ret;
    
    ret = mlock(&mtx);
        assert(ret == 0);
        
        assert(i == 4);
        assert(mtx.flag == Locked);
        assert(orderedQueueEmpty(mtx.waitingQueue));
    ret = munlock(&mtx);
    
    assert(ret == 0);
    assert(mtx.flag == Free);
    
    
    printf("\tTest Case 2 passed.\n");
    return;
}

void testMutex_lock() {
    int ret;
    i = 0;
    mmutex_init(&mtx);
    
    // TEST CASE 1
    ret = mlock(NULL);
    assert(ret == -1);
    printf("\tTest Case 1 passed.\n");
    
    // TEST CASE 2
    ret = mlock(&mtx);
        assert(ret == 0);
        assert(mtx.flag == Locked);
        assert(orderedQueueEmpty(mtx.waitingQueue));
        
        t2 = mcreate(testMutex_lock_f2, NULL);
        myield();
        
        assert(mtx.flag == Locked);
        assert(*((int*)(mtx.waitingQueue->begin->e)) == t2); // T2 must be in the wainting list
        
        t3 = mcreate(testMutex_lock_f3, NULL);
        myield();
        
        assert(mtx.flag == Locked);
        assert(*((int*)(mtx.waitingQueue->begin->e)) == t2); // T2 must be in the waiting list
        assert(*((int*)(mtx.waitingQueue->begin->next->e)) == t3); // T3 must be the second element in the waiting list
        
        // yield, but no other thread shall execute, therfore the flow must return immediatelly
        i = 0; // global
        i++;
        myield();
        assert(i == 1);
        
        i++;
    ret = munlock(&mtx);
    
    assert(ret == 0);
    assert(mtx.flag == Free);
    
    mjoin(t2);
    mjoin(t3);
    return;
}

void testMutex_unlock_f2() {
    int ret;
    
    ret = munlock(&mtx);
    
    assert(ret == -1);
    
    return;
}

void testMutex_unlock() {
    int ret;
    
    mmutex_init(&mtx);
    
    // TEST CASE 1
    ret = munlock(NULL);
    assert(ret == -1);
    printf("\tTest Case 1 passed.\n");
    
    // TEST CASE 2
    ret = munlock(&mtx);
    assert(ret == -1);
    printf("\tTest Case 2 passed.\n");
    
    // TEST CASE 3
    mlock(&mtx);
    ret = munlock(&mtx);
    assert(mtx.flag == Free);
    assert(ret == 0);
    printf("\tTest Case 3 passed.\n");
    
    // TEST CASE 4
    mlock(&mtx);
        mcreate(testMutex_unlock_f2, NULL);
        myield();
    ret = munlock(&mtx);
    assert(mtx.flag == Free);
    assert(ret == 0);
    printf("\tTest Case 4 passed.\n");
        
}

int main(int argc, char *argv[]) {
    
    printf("\nTesting mmutex_init ...\n");
    testMutex_init();
    printf("\tSuccess!\n\n");
    
    printf("\nTesting mlock ...\n");
    testMutex_lock();
    printf("\tSuccess!\n\n");
    
    printf("\nTesting munlock ...\n");
    testMutex_unlock();
    printf("\tSuccess!\n\n");
    
    return;
}

