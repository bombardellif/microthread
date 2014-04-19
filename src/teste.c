
/*
 * Programa exemplo de teste da biblioteca microthreads
 *
 * Versão 1 - 20/03/2014
 */

#include <stdio.h>
#include "mthread.h" /*considera que este fonte está no diretório testes (vide seção 8)*/

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

int main(int argc, char *argv[]) {
    int	id0, id1;
    int 	i;
    
	/* Código de execução */
	
    id0 = mcreate(func0, (void *)&i);
    id1 = mcreate(func1, (void *)&i);
	
	/* Código de execução */
	
    mjoin(id0);
    mjoin(id1);
}

