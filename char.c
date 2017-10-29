#include <stdio.h>
#include <stdlib.h>
#include "char.h"
#include <math.h>


t_pilha* aloca_pilha(){
	t_pilha* ptr = (t_pilha *) malloc(sizeof(t_pilha));
	ptr->topo = NULL;
	return ptr;
}

t_ele* aloca_elemento(float valor){
	t_ele* ptr = (t_ele *) malloc(sizeof(t_ele));
	ptr->dado = valor;
	ptr->ant = NULL;

	return ptr;
}


void push(t_pilha* pilha, float valor){

	t_ele* elemento = aloca_elemento(valor);
	if(pilha_vazia(pilha)){
		pilha->topo = elemento;
		elemento->ant = NULL;
	}
	else{
		elemento->ant = pilha->topo;
		pilha->topo = elemento;
	}
}

int pop(t_pilha* pilha){
	if(pilha_vazia(pilha)){
		printf("A pilha esta vazia\n");
		return 0;
	}
	int aux_return;
	t_ele* aux = pilha->topo;
	aux_return = pilha->topo->dado;
	pilha->topo = pilha->topo->ant;
	free(aux);
	return aux_return;
}


int pilha_vazia(t_pilha* pilha){
	return(pilha->topo == NULL);
}

int tam_pilha(t_pilha* pilha){
	int counter = 0;
	t_ele* atual = pilha->topo;
	while(atual != NULL){
		atual = atual->ant;
		counter++;
	}
	return counter;
}

void print_pilha(t_pilha* pilha){
	t_ele* aux = pilha->topo;
	if(pilha_vazia(pilha)){
		printf("Pilha vazia!");
	}
 	while(aux != NULL){
		printf("%.2f\n", aux->dado);
		aux = aux->ant;
	}
}

void libera_pilha(t_pilha* pilha){
	while(pilha->topo != NULL){
		t_ele* aux = pilha->topo;
		pilha->topo = pilha->topo->ant;
		free(aux); 
	}
	free(pilha);
}


