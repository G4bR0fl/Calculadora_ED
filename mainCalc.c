#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "char.h"
#include <string.h>
#include <math.h>

int main(){
	int mode;
	mode = menu();

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
	}
	if(mode == 2){
		modo_calc();
	}

	if(mode == 0){
		return 0;
	}
	

	return 0;
}