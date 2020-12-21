#include <inttypes.h>
#include <stdio.h>
#include "criptografia.h"


int main()
{
    printf("\t\t[Criptografia de arquivos!]\n");
    unsigned long long int p, q, y;
    int op;

    do {
        printf("\nDigite [0] para criptografar um arquivo");
        printf("\nDigite [1] para descriptografar um arquivo");
        printf("\nDigite [2] para sair");
        printf("\nOp: ");
        scanf("%d", &op);
        switch (op) {
            case 0 :
                Criar_arquivo_criptografado(&p, &q, &y);
                printf("\n<A Chave publica gerada eh e = [%llu], n = %llu\n", y, p * q);
                printf("\n<Arquivos de criptografia gerado com sucesso!\n");
                break;
            case 1 :
                Descriptografar_arquivo(y, p, q);
                printf("\n\n<Arquivo descriptografado gerado com sucesso!\n");
                break;
            case 2 :
                break;
            default :
                printf("\nOpcao invalida!");
        }
    } while (op != 2);

    return 0;
}
