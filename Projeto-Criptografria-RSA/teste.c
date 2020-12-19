#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//19 17 41

void maiscula(char *);
void criptografia(char *, int, int);
int gerar_d(int, int);
int dados[1000];
void descriptografia(int *, int, int, int);
bool primo(int);
bool coprimos(int, int);
FILE * modo_fptr(char *, char * );

int main()
{
    FILE *fptr;
    fptr = modo_fptr("texto.txt", "r");
    char frase[1000];
    int cont = -1, ch;
    printf(" <> O Texto a ser criptografado eh <>:\n");
    while( (ch = getc(fptr)) != EOF) {
          printf("%c", ch);
          cont++;
          frase[cont] = ch;
    }
    fclose(fptr);
    printf("\n\n");
    frase[++cont] = '\0';
    int p, q, y, mod;
    printf(">Informe o expoente: ");
    scanf("%d", &y);
    printf(">Informe o p: ");
    scanf("%d", &p);
    if(primo(p) == true) printf("O %d eh primo\n", p);
        else{
            while(primo(p) == false){
                printf("O %d nao eh primo, Informe Outro p: ", p);
                scanf("%d", &p);
            }
        }
    printf(">Informe o q: ");
    scanf("%d", &q);
    if(primo(q) == true) printf("O %d eh primo\n\n", q);
        else{
            while(primo(q) == false){
                printf("O  %d nao eh primo, Informe Outro q: ", q);
                scanf("%d", &q);
            }

        }
    if((coprimos((p - 1) * (q - 1), y)) == true) printf("O  %d e %d sao coprimos\n",(p - 1) * (q - 1), y);
     else {
            while((coprimos((p - 1) * (q - 1), y)) == false){
               printf("\nO  %d e %d nao sao coprimos , Informe Outro expoente: ",(p - 1) * (q - 1), y);
                scanf("%d", &y);
            }

        }
    mod = p * q;
    printf(">>A chave Gerada eh %d\n", mod);
    maiscula(frase);
    //puts(frase);
    criptografia(frase, y, mod);
    //gerar_d(y, (p - 1) * (q - 1));
    descriptografia(dados,gerar_d(y, (p - 1) * (q - 1)) , mod, cont );
    puts(">>Arquivos De Criptografia Criado com Sucesso!");


    return 0;
}

void maiscula(char frase[]) {
    int i;
    for(i = 0; frase[i] != '\0'; i++) {
      frase[i] = toupper(frase[i]);
     // printf("\ncaracter %c - valor ascii %d\n", frase[i], frase[i]);
    }

}

void criptografia(char frase[],int y, int mod) {
    int i, j, a, b, k = 0;
    FILE *fptr;
    fptr = modo_fptr("dadosCriptografados.txt", "w");


    for(i = 0; frase[i] != '\0'; i++) {
        a = frase[i] % mod ;
        //printf("a = %d\n", a);
        b = a;
        for(j = 1; j < y; j++) {
            a = a * b;
            a = a > mod ? a %= mod : a;
        }
        fprintf(fptr,"\n%d ^ %d = %d mod %d\t%c\t %d\n", frase[i], y, a, mod, frase[i], a);
        fprintf(fptr,"\n-----------------------------------\n\n");
        dados[++k] = a;
    }
    fclose(fptr);
}

int gerar_d(int y, int fi) {
    int i, d;
    for(i = 1; ; i++) {
       d = (i * y) % fi;
       if(d == 1) break;
    }
    //printf("\n**Sua chave privada eh: %d**\n", i);
    return i;
}

void descriptografia(int frase[],int y, int mod, int cont) {
    int i, j, a, b, k = -1;
    char palavra[1000];
    FILE *fptr;
    fptr = modo_fptr("dadosDescriptografados.txt", "w");


    for(i = 0; i <= cont; i++) {
        a = frase[i] % mod ;
        //printf("a = %d\n", a);
        b = a;
        for(j = 1; j < y; j++) {
            a = a * b;
            a = a > mod ? a %= mod : a;
        }
        k++;
        palavra[k] = a;
        //printf("CARACTER = %c\n", palavra[k]);
        fprintf(fptr, "\n%d ^ %d =  %d [%c]  mod %d\n", frase[i], y, a, a, mod);
        fprintf(fptr, "\n\n-----------------------------------\n\n");
    }
       // palavra[k++] = '\0';
        //fprintf(fptr,"\n%s", fptr);
        for(i = 0; i < cont; i++) {
        putc(tolower(palavra[i]), fptr);
        }
    fclose(fptr);

}
bool primo(int m)
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

bool coprimos(int a, int b) {
    int c, d;
    do {
        c = a / b;
        d = a - c * b;
        //printf("a = %d ; b = %d ; c = %d; d = %d\n\n",  a, b, c ,d);
        a = b;
        b = d;
       } while( d != 0 );
        if(a == 1) return true;
        else return false;

}

FILE * modo_fptr(char arq1[], char modo[]) {
    FILE *fptr;
    if( (fptr = fopen(arq1, modo)) == NULL) {
        puts("Erro ao Abrir Arquivo");
    }
    return fptr;
}
