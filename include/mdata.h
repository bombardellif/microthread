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

/**
 * Compare two int pointers, returns 0 iff the content pointed by a is equal (natural comparison) to the content pointed by b, returns 1 iff a's content is greater than b's, returns -1 iff a's content is less than b's
 * @param a First argument to be compared
 * @param b Second argument to be compared
 * @return Semantically speaking, 0 iff a is equal to b, 1 iff a > b, -1 otherwise
 */
int intPointerCompare(int* a, int* b){
    return (*a == *b) ? 0 : ((*a > *b) ? 1 : -1);
}
