 /*
 *
 * Prototipos das operações realizadas para o projeto de criptografia-rsa.
 *
 * Felipe Ferreira
 */
#ifndef _CRIPTOGRAFIA_H
#define _CRIPTOGRAFIA_H

#include <stdbool.h>
#include <stdio.h>

#define MAX_TEXT 100000
#define MAX_EXP 20
#define LIM_IMPRESSAO 300
#define LIM_PRIMOS 100

/*
*
* Funcao publica responsavel por criar o arquivo criptografado
*/
void Criar_arquivo_criptografado(int *, int *, int *);

/*
*
* Funcao publica responsavel por criar o arquivo descriptografado
*/
void Descriptografar_arquivo();

#endif // _CRIPTOGRAFIA_H
