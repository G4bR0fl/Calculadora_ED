#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main(){
	t_pilha* pilha = aloca_pilha();
	read_expression(pilha);
	return 0;
}