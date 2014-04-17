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
#define True 1;
#define False 0;


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

/**
 * Compare the time of execution of two TCBs, return 0 (Zero) if both are equals,
 * returns a number greater than 0 if a's time is greater than b's, and returns
 * a number less than 0 if b's time is greater than a's one.
 * @param a
 * @param b
 * @return int  0 if equal, greater than 0 if a>b, less than 0 else
 */
int executedTimeTcbCompare(Tcb* a, Tcb* b) {
    return a->executedTime - b->executedTime;
}
