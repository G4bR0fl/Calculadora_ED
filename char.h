#ifndef __CHAR_H__
#define __CHAR_H__
#include <math.h>

typedef struct elemento{
	struct elemento* ant;
	float dado;
}t_ele;

typedef struct {	
	t_ele* topo;
}t_pilha;

t_pilha* aloca_pilha();
t_ele* aloca_elemento(float valor);

void push(t_pilha* pilha, float valor);
int pop(t_pilha* pilha);
int pilha_vazia(t_pilha* pilha);
int tam_pilha(t_pilha* pilha);
void libera_pilha(t_pilha* pilha);
void print_pilha(t_pilha* pilha);




#endif