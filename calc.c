#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "char.h"
#include <string.h>

int read_expression(char* expressao){

	char operador;
	int i, flag_true;
	flag_true = 1;
	i = 0;
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
	
	if(flag_true == 0 || !pilha_vazia(pilha)){
		libera_pilha(pilha);
		pilha = NULL;
		return 0;/*Verificar na compilacao se ta certo essas 5 linhas*/
		//retornar pro menu e esvaziar a pilha
	}
	else{
		return 1;
		//retonar a expressao e continuar
	}
}

int prioridade(char* expressao, t_pilha* pilha, int counter){
	int prioridade;

		if(expressao[counter] == '+' || expressao[counter] == '-'){
			prioridade = 1;
			return prioridade;
		}
		if(expressao[counter] == '*' || expressao[counter] == '/'){
			prioridade = 2;
			return prioridade;
		}
	if(expressao[counter] == '\0'){
		return -1;
	}
}

void infixa_to_posfixa(char* expressao){
	char str_aux[101];//teste com str estatica
	int prio_ant;
	t_pilha* pilha = aloca_pilha();
	int i = 0, j = 0, k = 0;
	while(expressao[k] != '\0'){
		if(expressao[i] != '+' && expressao[i] != '-'
			&&  expressao[i] != '*' &&  expressao[i] != '/' 
			&&  expressao[i] != '(' &&  expressao[i] != '['
			&&  expressao[i] != '{' &&  expressao[i] != ')'
			&&  expressao[i] != ']' &&  expressao[i] != '}'
			&& expressao[i] != '\0')
		{
			str_aux[j] = expressao[i];
			i++;
			j++;
			k++;
		}
		else{
			if((prioridade(expressao, pilha, i) == 1 && pilha_vazia(pilha)) || prioridade(expressao, pilha, i) == 2 && pilha_vazia(pilha)){
				push(pilha, expressao[i]);
				prio_ant = prioridade(expressao, pilha, i);
				i++;
			}
			else{
				if(prioridade(expressao, pilha, i)  == 1 && !pilha_vazia(pilha)){
					
						str_aux[j] = pop(pilha);
						push(pilha, expressao[i]);
						j++;
						k++;
						prio_ant = prioridade(expressao, pilha, i);
						i++;
					
				}
				else{
					if(prioridade(expressao, pilha, i) == 2 && !pilha_vazia(pilha)){
						
							str_aux[j] = pop(pilha);
							push(pilha, expressao[i]);
							j++;
							k++;
							prio_ant = prioridade(expressao, pilha, i);
							i++;
						
					}
					else{
						if(prioridade(expressao, pilha, i) == -1 && !pilha_vazia(pilha)){
							str_aux[j] = pop(pilha);
							j++;
							k++;
						}
					}
				}
			}
		}
	}
	str_aux[k] = '\0';
	printf("Infixa: %s\nPosfixa: %s\n", expressao, str_aux);
}