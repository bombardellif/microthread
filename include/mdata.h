/*
 * mdata.h: arquivo de inclusão onde os grupos devem colocar as definições
 *          de suas estruturas de dados
 *
 * VERSÃO 1 - 20/03/2014
 */
 
typedef int uth_id;
typedef char boolean;
/*
 * Exemplo de estrutura de dados "mutex"
 * Os grupos devem alterar essa estrutura de acordo com sua necessidade
 */ 
typedef struct mutex {
	int flag;
    //TCB *next;
} mmutex_t;
