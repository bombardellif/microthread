/*
 * mdata.h: arquivo de inclusão onde os grupos devem colocar as definições
 *          de suas estruturas de dados
 *
 * VERSÃO 1 - 20/03/2014
 */

#ifndef MDATA_H
#define	MDATA_H

#define TRUE 1
#define FALSE 0
#define ERR_MCREATE -1
#define NOTHING_EXECUTE_ERRMSG "Nothing to execute"

typedef char boolean;

typedef struct SListElem ListElem;

struct SListElem{
    void *e;
    ListElem *prev;
    ListElem *next;
};

typedef struct SListDesc{
    ListElem *begin;
    ListElem *end;
} List;

//"Extends" List
typedef List OrderedQueue;

typedef enum {Locked, Free} MutexFlag;

typedef struct Smmutex_t{
    MutexFlag flag;
    int ownerThread;
    OrderedQueue* waitingQueue;
} mmutex_t;

#endif
