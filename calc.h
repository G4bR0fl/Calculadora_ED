#ifndef __CALC_H__
#define __CALC_H__
#include "char.h"

int read_expression(char* expressao);
void infixa_to_posfixa(char* expressao);
int prioridade(char* expressao, t_pilha* pilha, int counter);
void modo_calc();
int menu();

#endif