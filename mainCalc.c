#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "char.h"
#include <string.h>
#include <math.h>

int main(){//fazer um while grande pra so sair dado um return das 3 funcoes
	int mode, receiver;
	mode = menu();
	while(mode == 1 || mode == 2){
		if(mode == 1){
			char* expressao = (char *) malloc(sizeof(char)*100);

			printf("Informe a expressao na forma infixa: ");
			scanf("%[^\n]s", expressao);
			getchar();
			read_expression(expressao);

			if(read_expression(expressao) == 0){
				printf("A expressao nao eh valida\n");
			}
			if(read_expression(expressao) == 1){
				printf("A expressao eh valida\n");
			}

			receiver = infixa_to_posfixa(expressao);

			if(receiver == 1){
				menu();
			}

		}
		if(mode == 2){
			modo_calc();
			if(modo_calc() == 100){
				menu();
			}
		}

		if(mode == 0){
			return 0;
		}
	}

	return 0;
}