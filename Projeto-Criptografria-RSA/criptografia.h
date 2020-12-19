#ifndef _CRIPTOGRAFIA_H
#define _CRIPTOGRAFIA_H

#include <stdbool.h>
#include <stdio.h>
#define MAX_TEXT 100000
#define MAX_EXP 20
#define LIM_IMPRESSAO 300



void Criar_arquivo_criptografado(int *, int *, int *);

void Descriptografar_arquivo();

FILE * modo_fptr(char *, char * );

#endif // _CRIPTOGRAFIA_H
