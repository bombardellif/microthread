/*
 * mdata.h: arquivo de inclusão onde os grupos devem colocar as definições
 *          de suas estruturas de dados
 *
 * VERSÃO 1 - 20/03/2014
 */

#define TRUE 1
#define FALSE 0

typedef int uth_id;
typedef char boolean;


typedef struct Smmutex_t{
    int flag;
    OrderedQueue waitingQueue;
} mmutex_t;
