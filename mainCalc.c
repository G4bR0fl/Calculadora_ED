#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "char.h"
#include <string.h>

int main(){
	
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

	infixa_to_posfixa(expressao);

	return 0;
}