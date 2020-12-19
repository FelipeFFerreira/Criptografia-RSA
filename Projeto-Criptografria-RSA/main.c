#include "criptografia.h"
#include <stdio.h>

//19 17 41


int main()
{
    int p, q, y, op;
    do {
        printf("\nDigite [0] para criptografar um arquivo");
        printf("\nDigite [1] para descriptografar um arquivo");
        printf("\nDigite [2] para sair");
        printf("\nOp: ");
        scanf("%d", &op);
        switch (op) {
            case 0 :
                Criar_arquivo_criptografado(&p, &q, &y);
                printf("\n<A Chave publica gerada eh e = [%d], n = %d\n", y, p * q);
                printf("\n<Arquivos de criptografia gerado com sucesso!");
                break;
            case 1 :
                Descriptografar_arquivo(y, p, q);
                printf("\n<Arquivo de descriptografado gerado com sucesso!");
                break;
            case 2 :
                break;
            default :
                printf("\nOpcao invalida!");
        }
    } while (op != 2);

    return 0;
}
