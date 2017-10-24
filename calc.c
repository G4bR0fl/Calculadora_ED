#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "char.h"

void read_expression(){
	char expressao[101], operador;
	int i, flag_true;
	flag_true = 1;
	i = 0;
	printf("Informe a expressao na forma infixa: ");
	scanf("%[^\n]s", expressao);
	getchar();
	t_pilha* pilha = aloca_pilha();
	while(expressao[i] != '\0' && flag_true == 1){
		if(expressao[i] == '(' || expressao[i] == '[' || expressao[i] == '{'){
			push(pilha, expressao[i]);
		}//Condicional para ver um operador de inicio
		if(expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}'){
			if(pilha_vazia(pilha)){
				flag_true = 0;
			}
			else{
				operador = (char) pop(pilha);
				 if(operador == '(' && expressao[i] != ')'){
				 	flag_true = 0;
				 }
				 if(operador == '[' && expressao[i] != ']'){
				 	flag_true = 0;
				 }
				 if(operador == '{' && expressao[i] != '}'){
				 	flag_true = 0;
				 }
			}
		}//Condicional para ver o operador de final
		i++;
	}
	printf("\nA expressao");
	if(flag_true == 0 || !pilha_vazia(pilha)){
		printf(" nao eh valida\n");
	}
	else{
		printf(" eh valida\n");
	}
	libera_pilha(pilha);
	pilha = NULL;
}