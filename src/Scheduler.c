/* 
 * File:   Scheduler.c
 * Author: fernando
 *
 * Created on 15. April 2014, 23:56
 */

#include "mdata.h"
#include "Tcb.h"
#include <ucontext.h>
#include <stdlib.h>

#include <assert.h>

//static OrderedQueue readyQueue;
//static List threadList;
static Tcb* executingThread = NULL;
static boolean yielding;
static ucontext_t terminateContext;


/**
 * Essa função altera o estado de yielding do escalonador (Verdadeiro ou Falso)
 * @param yield
 */
void setYielding(boolean yield) {
    yielding = yield;
}

/**
 * Esse procedimento deve salvar o contexto atual na TCB da thread em execução.
 * 
 */
void saveContext() {
    // assertion
    assert(executingThread != NULL);
    
    getcontext(&(executingThread->context));
}

/**
 * Retorna o struct do context que deve ser coloca a executar ao finalizar uma 
 * thread.
 * @return ucontext_t*  Ponteiro para o contexto a executar ao finlaizar thread.
 */
ucontext_t* getTerminateContext() {
    ucontext_t tmpContext;
    
    // Se ainda não gerou o contexto, então o gera
    if (!terminateContext) {
        
        getcontext(&tmpContext);
        
        /* Se a variável global terminateContext tiver algum valor diferente de NULL,
         * então ela já foi atribuída, logo a execução chegou aqui por meio do fim
         * de alguma thread. Logo chama a função de terminação de thread.           */
        if (terminateContext) {
            
            // Atenção: Essa chamada abaixo não retornará, pois ela chama o scheduler,
            // que coloca outro contexto a executar sem salvar o atual (que está finalizando)
            terminateThread();
        } else {
            terminateContext = tmpContext;
        }
    }
    
    return terminateContext;
}

/**
 * Retorna o TCB da thread em execução.
 * @return Tcb*
 */
Tcb* getExecutingThread() {
    return executingThread;
}

void terminateThread() {
    
}