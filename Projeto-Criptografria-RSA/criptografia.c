#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "criptografia.h"

static bool primo(int m)
{
    if (m == 1)
        return false;
    if (m == 2)
        return true;
    if (m % 2 == 0)
        return false;
    int i;
    for (i = 3; i <= (int) sqrt(m); i += 2) {
        if (m % i == 0)
            return false;
    }
    return true;
}

static bool coprimos(int a, int b)
{
    int c, d;
    do {
        c = a / b;
        d = a - c * b;
        a = b;
        b = d;
       } while( d != 0 );
        if(a == 1) return true;
        else return false;
}

static void Scanf_number_primo(int * n)
{
    int q;
    scanf("%d", &q);
    if (primo(q))
        printf("<O %d e primo!\n\n", q);
        else {
            while (!primo(q)){
                printf("<[%d] nao e primo, Informe outro numero: ", q);
                scanf("%d", &q);
            }
        }
    *n = q;
}

static void list_coprimos_existentes(int p, int q)
{
    int i, cont = 0, n = p * q;
    printf("<Existem %d numeros coprimos disponiveis para escolha do expoente:\n", (p - 1) * (q - 1));
    printf("<Lista com os %d coprimos:\n",MAX_EXP);
    for (i = 1; i < MAX_EXP; i++)
        if (coprimos(n, i))
            printf("%d- %d\n", ++cont, i);
}

static void inicializar_leitura_arquivo(char * texto)
{
    FILE *fptr;
    int cont = 0, cont_lim = 0, ch;
    fptr = modo_fptr("texto.txt", "r");
    printf("\n<Texto a ser criptografado encontrado e carregado\n\n");
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
     // printf("\ncaracter %c - valor ascii %d\n", str[i], str[i]);
    }
}

static int gerar_d(int y, int fi) {
    int i, d;
    for (i = 1; ; i++) {
       d = (i * y) % fi;
       if (d == 1) break;
    }
    //printf("\n**Sua chave privada eh: %d**\n", i);
    return i;
}

static void criptografar(char * str, int y, int mod)
{
    int i, j, a, b;
    char nome_arq[31];
    FILE *fptr, *fptr_1;
    fptr = modo_fptr("Mat_modu_cripto.txt", "w");
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
        fprintf(fptr,"\n%d ^ %d mod %d = %d\t[%c] -->\t[%d]\n", str[i], y, mod, a, str[i], a);
        fprintf(fptr_1, "%d%c", a, '.');
    }
    fclose(fptr);
    fclose(fptr_1);
}

static void descriptografar(int y, int mod) {
    int i, j, a, b, k = 0;
    int texto[MAX_TEXT];
    int cont = 0, cont_lim = 0, ch;
    char str_aux[10], nome_arq[8];
    FILE *fptr, *fptr_1;
    printf("\n<Infome o nome do arquivo onde encontra-se os dados criptografados: ");
    scanf( "%s[^\n]", nome_arq);
    fptr = modo_fptr(nome_arq, "r");
    fptr_1 = modo_fptr("Dados_descriptografados.txt", "w");
    printf("\n<Texto a ser descriptografado encontrado e carregado\n\n");
    while ((ch = getc(fptr)) != EOF) {
          if (cont_lim++ < LIM_IMPRESSAO) printf("%d", ch);
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
    printf("\n\n");
    for (i = 0; texto[i] != '\0'; i++) {
        a = texto[i] % mod ;
        b = a;
        for (j = 1; j < y; j++) {
            a = a * b;
            a = a > mod ? a %= mod : a;
        }
        //fprintf(fptr, "\n%d ^ %d =  %d [%c]  mod %d\n", texto[i], y, a, a, mod);
        //fprintf(fptr, "\n\n-----------------------------------\n\n");
        fprintf(fptr_1, "%c", a);
    }

    fclose(fptr_1);
}

void Criar_arquivo_criptografado(int * P, int * Q, int * Y)
{
    int p, q, y;
    char str[MAX_TEXT];
    inicializar_leitura_arquivo(str);
    printf(">Informe o p: ");
    Scanf_number_primo(&p);
    printf(">Informe o q: ");
    Scanf_number_primo(&q);
    list_coprimos_existentes(p, q);

    printf("\n>Informe o expoente: ");
    scanf("%d", &y);
    if (coprimos(p * q, y))
        printf("<[%d] e [%d] sao coprimos!\n", p  * q , y);
     else {
            while (!(coprimos(p * q , y))) {
                printf("\n<[%d] e [%d] nao sao coprimos, informe outro expoente: ",(p - 1) * (q - 1), y);
                scanf("%d", &y);
            }
        }
    *P = p;
    *Q = q;
    *Y = y;
    maiscula(str);
    criptografar(str, y, p * q);
}

void Descriptografar_arquivo(int y, int p, int q)
{
    descriptografar(gerar_d(y, (p - 1) * (q - 1)) , p * q);
}

FILE * modo_fptr(char arq1[], char modo[]) {
    FILE *fptr;
    if( (fptr = fopen(arq1, modo)) == NULL) {
        puts("Erro ao Abrir Arquivo");
    }
    return fptr;
}
