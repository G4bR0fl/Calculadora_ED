#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "char.h"
#include <string.h>
#include <math.h>

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
		return 1;
	}
	if(expressao[counter] == '*' || expressao[counter] == '/'){
		return 2;
	}
	if(expressao[counter] == '\0'){
		return -1;
	}
	if(expressao[counter] == '('){
		return 5;
	}
	if(expressao[counter] == '['){
		return 4;
	}
	if(expressao[counter] == '{'){
		return 3;
	}
}

void infixa_to_posfixa(char* expressao){ /*Incompleta, ainda muita coisa a fazer e mudar o tipo pra retornar str_aux*/
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
		//Para os operadores:
		else{
			if( (prioridade(expressao, pilha, i) == 1 && pilha_vazia(pilha)) || prioridade(expressao, pilha, i) == 2 && pilha_vazia(pilha) ){
				push(pilha, expressao[i]);
				prio_ant = prioridade(expressao, pilha, i);
				i++;
			}
			else{
				if(prioridade(expressao, pilha, i)  == 1 && !pilha_vazia(pilha)){
					if(prio_ant < prioridade(expressao, pilha, i)){
						push(pilha, expressao[i]);
						prio_ant = prioridade(expressao, pilha, i);
						i++;
					}
					else{
						if(prio_ant >= prioridade(expressao, pilha, i)){
							str_aux[j] = pop(pilha);
							push(pilha, expressao[i]);
							i++;
							k++;
							j++;
						}
					}
				}
				else{
					if(prioridade(expressao, pilha, i) == 2 && !pilha_vazia(pilha)){
						if(prio_ant < prioridade(expressao, pilha, i)){
							push(pilha, expressao[i]);
							prio_ant = prioridade(expressao, pilha, i);
							i++;
						}
						else{
							if(prio_ant >= prioridade(expressao, pilha, i)){
								str_aux[j] = pop(pilha);
								push(pilha, expressao[i]);
								i++;
								k++;
								j++;
							}
						}
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
			//Para os parenteses, colchetes e chaves:
			if( (prioridade(expressao, pilha, i) == 3 && pilha_vazia(pilha)) || (prioridade(expressao, pilha, i) == 4 && pilha_vazia(pilha)) || (prioridade(expressao, pilha, i) == 5 && pilha_vazia(pilha)) )
			{
				push(pilha, expressao[i]);
				i++;
				k++;
				j++;
				//prio_op = prioridade(expressao, pilha, i);
			}
			else{
				if( (prioridade(expressao, pilha, i) == 5 && !pilha_vazia(pilha)) || (prioridade(expressao, pilha, i) == 4 && !pilha_vazia(pilha)) || (prioridade(expressao, pilha, i) == 3 && !pilha_vazia(pilha)) ){
					push(pilha, expressao[i]);
					i++;
					prio_ant = 0;
				}
				else{
					if(expressao[i] == ')' || expressao[i] == ']' || expressao[i] == '}'){
						while((char)pilha->topo->dado == '*' || (char) pilha->topo->dado == '/' || (char) pilha->topo->dado == '+' || (char) pilha->topo->dado == '-'){
							if((char) pilha->topo->dado == '(' || (char) pilha->topo->dado == '[' || (char) pilha->topo->dado == '{'){
								pop(pilha);
								if(!pilha_vazia(pilha)){
									while(!pilha_vazia(pilha)){
										str_aux[j] = pop(pilha);
										j++;
										k++;
									}
								}
								break;
							}
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

void modo_calc(){
	t_pilha* pilha = aloca_pilha();
	char check[100];
	float numero_final, mult, operacao_pilha = 0;
	int i = 0, size = 0, dec = 0, counter_dec = 0, size_mult_dec , size_mult_int;
	printf("Modo Calculadora:\n");
	if(pilha_vazia(pilha)){
		printf("Pilha Vazia!\n");
	}

	printf("Informe um valor('0' para sair ou pressione 'space'): ");
	scanf("%[^\n]s", check);
	getchar();
		for(i = 0; i <= strlen(check); i++){
			if(check[0] == ' ' || check[0] == '0'){
				printf("Usuario digitou space ou 0\n");
				libera_pilha(pilha);
				pilha = NULL;
				exit(0);
			}
		}			

	while(check[0] == '+' || check[0] == '-' || check[0] == '*' || check[0] == '/'){
		printf("Numero insuficiente de operandos!\n");
		printf("Informe um valor('0' ou space para sair): ");
		scanf("%[^\n]s", check);
		getchar();
		if(check[0] == ' ' || check[0] == '0'){
			printf("Usuario digitou space ou 0\n");
			libera_pilha(pilha);
			pilha = NULL;
			exit(0);
		}
	}


	for(i = 0; i < strlen(check); i++){
		if(check[i] == '.'){
			dec = 1; 
			break;
		}
		else{
			counter_dec++;
		}
	}
	numero_final = 0;
	size_mult_int = counter_dec -1;
	size_mult_dec = ((counter_dec+1) - strlen(check));
	//Transformacao de char pra double:
	for(i = 0; i < strlen(check); i++){
		if(check[i] != '.'){
			if(size_mult_int >= 0){
				mult = pow(10, size_mult_int);
				size_mult_int--;
			}
			else{
				mult = pow(10, size_mult_dec);
				size_mult_dec--;
			}
			numero_final += ((float)check[i] - 48) * mult;
		}
	}

	while(check[0] != '0'){
		if(check[0] != '+' && check[0] != '-' && check[0] != '*' && check[0] != '/' && check[1] != '!'){
			push(pilha, numero_final);
			size++;
			printf("Topo: ");
			print_pilha(pilha);
		}
		numero_final = 0;
		mult = 0;
		counter_dec = 0;
		printf("Informe um valor('0' ou 'space' para sair), ou um operador: ");
		scanf("%[^\n]s", check);
		getchar();
		if(check[0] == '0' || check[0] == ' '){
			printf("O usuario encerrou.\n");
			libera_pilha(pilha);
			pilha = NULL;
			exit(0);
		}

		if(size < 2 && ((check[0] == '+') || (check[0] == '-') || (check[0] == '*') || (check[0] == '/')) ){
			printf("Numero de operandos insuficientes!\n");
			do
			{	
				printf("Informe um valor('0' ou 'space' para sair): ");
				scanf("%[^\n]s", check);
				getchar();
				if(check[0] == '0' || check[0] == ' '){
					printf("O usuario encerrou.\n");
					libera_pilha(pilha);
					exit(0);
				}
			} while (check[0] == '+' || check[0] == '-' || check[0] == '*' || check[0] == '/');
		}

		if(check[0] != '+' && check[0] != '-' && check[0] != '*' && check[0] != '/' && check[0] != 'c' ){
				for(i = 0; i < strlen(check); i++){
				if(check[i] == '.'){
					dec = 1; 
					break;
				}
				else{
					counter_dec++;
				}
			}
			size_mult_int = counter_dec -1;
			size_mult_dec = ((counter_dec+1) - strlen(check));
			//Transformacao de char pra double:
			for(i = 0; i < strlen(check); i++){
				if(check[i] != '.'){
					if(size_mult_int >= 0){
						mult = pow(10, size_mult_int);
						size_mult_int--;
					}
					else{
						mult = pow(10, size_mult_dec);
						size_mult_dec--;
					}
					numero_final += ((float)check[i] - 48) * mult;
				}
			}
		}
		else{
			if(check[0] == '+' && check[1] != '!'){
				operacao_pilha = pop(pilha);
				operacao_pilha += pilha->topo->dado;
				pilha->topo->dado = operacao_pilha;
				print_pilha(pilha);
				size--;
				operacao_pilha = 0;
			}
			if(check[0] == '-' && check[1] != '!'){
				operacao_pilha = pop(pilha);
				operacao_pilha -= pilha->topo->dado;
				pilha->topo->dado = operacao_pilha;
				print_pilha(pilha);
				size--;
				operacao_pilha = 0;
			}
			if(check[0] == '*' && check[1] != '!'){
				operacao_pilha = pop(pilha);
				operacao_pilha *= pilha->topo->dado;
				pilha->topo->dado = operacao_pilha;
				print_pilha(pilha);
				size--;
				operacao_pilha = 0;
			}
			if(check[0] == '/'){
				operacao_pilha = pop(pilha);
				operacao_pilha /= pilha->topo->dado;
				pilha->topo->dado = operacao_pilha;
				print_pilha(pilha);
				size--;
				operacao_pilha = 0;
			}
			if(check[0] == '+' && check[1] == '!'){
				while(!pilha_vazia(pilha)){
					operacao_pilha += pop(pilha);
					size = 0;
				}
				push(pilha, operacao_pilha);
				size++;
				printf("Topo: ");
				print_pilha(pilha);
				operacao_pilha = 0;
			}
			if(check[0] == '-' && check[1] == '!'){
				operacao_pilha += pop(pilha);
				while(!pilha_vazia(pilha)){
					operacao_pilha -= pop(pilha);
					size = 0;
				}
				push(pilha, operacao_pilha);
				size++;
				printf("Topo: ");
				print_pilha(pilha);
				operacao_pilha = 0;
			}
			if(check[0] == '*' && check[1] == '!'){
				operacao_pilha += pop(pilha);
				while(!pilha_vazia(pilha)){
					operacao_pilha *= pop(pilha);
					size = 0;
				}
				push(pilha, operacao_pilha);
				size++;
				printf("Topo: ");
				print_pilha(pilha);
				operacao_pilha = 0;
			}
		}
	}
	exit(0);
}


int menu(){
	int mode;
	printf("1- Modo Expressao\n");
	printf("2- Modo Calculadora\n");
	printf("0- Para sair\n");
	printf("Escolha um modo: ");
	scanf("%d", &mode);
	getchar();
	return mode;
}
