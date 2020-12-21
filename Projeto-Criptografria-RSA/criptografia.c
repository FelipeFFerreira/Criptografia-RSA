 /*
 *
 * Implementacao das operações para o projeto de criptografia-rsa.
 *
 * Felipe Ferreira
 */
#include <inttypes.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <math.h>
#include <stdbool.h>
#include "criptografia.h"

/*
* Area de funcoes privadas
*
*/
static FILE * modo_fptr(char arq1[], char modo[]) {
    FILE *fptr;
    if( (fptr = fopen(arq1, modo)) == NULL) {
        puts("Erro ao Abrir Arquivo");
    }
    return fptr;
}

static bool primo(unsigned long long int m)
{
    if (m == 1)
        return false;
    if (m == 2)
        return true;
    if (m % 2 == 0)
        return false;
    int i;
    for (i = 3; i <= (unsigned long long int) sqrt(m); i += 2) {
        if (m % i == 0)
            return false;
    }
    return true;
}

static bool coprimos(unsigned long long int a, unsigned long long int b)
{
    unsigned long long int c, d;
    do {
        c = a / b;
        d = a - c * b;
        a = b;
        b = d;
       } while( d != 0 );
        if(a == 1) return true;
        else return false;
}

static void scanf_number_primo(unsigned long long int * n)
{
    unsigned long long int q;
    scanf("%llu", &q);
    if (primo(q))
        printf("<O %llu e primo!\n\n", q);
        else {
            while (!primo(q)){
                printf("<[%llu] nao e primo, Informe outro numero: ", q);
                scanf("%llu", &q);
            }
        }
    *n = q;
}

static void list_numbers_primos()
{
    int i, j;
    printf("\n<Utilize primos maiores que 100\n");
    printf("Alguns numeros primos\n");
    for (i = 101, j = 0; j < LIM_PRIMOS - 1; i++) {
        if (primo(i)) {
            printf("%d, ", i);
            j++;
        }
    }
    printf("\n\n");
}

static void list_coprimos_existentes(unsigned long long int p, unsigned long long int q)
{
    int i, j;
    unsigned long long int totiente = (p - 1) * (q - 1);
    printf("<Existem %llu numeros coprimos de %llu disponiveis para escolha do expoente:\n", totiente, p * q);
    printf("<Lista com os %d coprimos:\n", MAX_EXP);
    for (i = 1, j = 0; j < MAX_EXP && j < totiente; i++)
        if (coprimos(totiente, i))
            printf("%d. %d\n", ++j, i);
}

static void inicializar_leitura_arquivo(char * texto)
{
    FILE *fptr;
    int cont = 0, cont_lim = 0, ch;
    fptr = modo_fptr("texto.txt", "r");
    printf("\n<Texto a ser criptografado encontrado e carregado\n");
    printf("\"");
    while ((ch = getc(fptr)) != EOF) {
          if (cont_lim++ < LIM_IMPRESSAO) printf("%c", ch);
          texto[cont++] = ch;
    }
    printf(" .... ");
    printf("\"\n\n");
    fclose(fptr);
    texto[cont++] = '\0';
}

static void maiscula(char str[]) {
    int i;
    for(i = 0; str[i] != '\0'; i++) {
      str[i] = toupper(str[i]);
    }
}

static unsigned long int gerar_d(unsigned long long int y, unsigned long long int fi) {
    unsigned long int i;
    unsigned long long int d;
    for (i = 1; ; i++) {
       d = (i * y) % fi;
       if (d == 1) break;
    }
    //printf("\n**Sua chave privada eh: %d**\n", i);
    return i;
}

static void criptografar(char * str, unsigned long long  int y, unsigned long long int mod)
{
    unsigned long int i, j;
    unsigned long long int a, b;
    char nome_arq[31];
    FILE *fptr, *fptr_1;
    fptr = modo_fptr("Mat_criptografia.txt", "w");
    printf("\n<Infome o nome do arquivo que armazenara os dados criptografados: ");
    scanf(" %s[^\n]", nome_arq);
    fptr_1 = modo_fptr(nome_arq, "w");

    for (i = 0; str[i] != '\0'; i++) {
        a = str[i] % mod ;
        b = a;
        for (j = 1; j < y; j++) {
            a = a * b;
            a = a > mod ? a %= mod : a;
        }
        fprintf(fptr,"\n%llu ^ %llu mod %llu = %llu\t[%c] -->\t[%llu]\n", str[i], y, mod, a, str[i], a);
        fprintf(fptr_1, "%llu%c", a, '.');
    }
    printf("\n<Dados Criptografados com sucesso!\n");
    fclose(fptr);
    fclose(fptr_1);
}

static void descriptografar(unsigned long long int y, unsigned long long int mod) {
    int i, j, k = 0;
    unsigned long long int a, b;
    int texto[MAX_TEXT];
    int cont = 0, cont_lim = 0, ch;
    char str_aux[10], nome_arq[8];
    FILE *fptr, *fptr_1, *fptr_2;
    printf("\n<Infome o nome do arquivo onde encontra-se os dados criptografados: ");
    scanf( "%s[^\n]", nome_arq);
    fptr = modo_fptr(nome_arq, "r");
    fptr_1 = modo_fptr("Dados_descriptografados.txt", "w");
    fptr_2 = modo_fptr("Mat_descriptografia.txt", "w");
    printf("\n<Texto a ser descriptografado encontrado e carregado\n");
    printf("Processando ...\n\n");
    while ((ch = getc(fptr)) != EOF) {
          if (cont_lim++ < LIM_IMPRESSAO) printf("%llu", ch);
          if (ch != '.')
                str_aux[k++] = ch;
            else {
                str_aux[k] = '\0';
                texto[cont++] = atoi(str_aux);
                k = 0;
            }
    }
    fclose(fptr);
    texto[cont++] = '\0';
    for (i = 0; texto[i] != '\0'; i++) {
        a = texto[i] % mod ;
        b = a;
        for (j = 1; j < y; j++) {
            a = a * b;
            a = a > mod ? a %= mod : a;
        }
        fprintf(fptr_2,"\n%llu ^ %llu mod %llu \t= \t[%c]\n", texto[i], y, mod, a);
        fprintf(fptr_1, "%c", tolower(a));
    }
    fclose(fptr_1);
    fclose(fptr_2);
    printf("\n<Dados descriptografados com sucesso!\n");
}

/*
*
* Area de funcoes publicas
*/
void Criar_arquivo_criptografado(unsigned long long int * P, unsigned long long int * Q, unsigned long long int * Y)
{
    unsigned long long int p, q, y;
    char str[MAX_TEXT];
    inicializar_leitura_arquivo(str);
    list_numbers_primos();
    printf(">Informe o p: ");
    scanf_number_primo(&p);
    printf(">Informe o q: ");
    scanf_number_primo(&q);
    list_coprimos_existentes(p, q);

    printf("\n>Informe o expoente: ");
    scanf("%llu", &y);
    if (coprimos(p * q, y))
        printf("<[%llu] e [%llu] sao coprimos!\n", p  * q , y);
     else {
            while (!(coprimos(p * q , y))) {
                printf("\n<[%llu] e [%llu] nao sao coprimos, informe outro expoente: ", (p - 1) * (q - 1), y);
                scanf("%llu", &y);
            }
        }
    *P = p;
    *Q = q;
    *Y = y;
    maiscula(str);
    criptografar(str, y, p * q);
}

void Descriptografar_arquivo(unsigned long long int y, unsigned long long int p, unsigned long long int q)
{
    descriptografar(gerar_d(y, (p - 1) * (q - 1)) , p * q);
}
