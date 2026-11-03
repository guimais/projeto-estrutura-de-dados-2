#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Apoio.h"

int main()
{
    Arv *Arvore = Criar_Arvore();
    int Opcao, valor;

    do{
        system("cls");
        printf("**************************************************************");
        printf("\n Sistema de Gerenciamento de Falhas em Equipamentos");

        printf("\n\n\tDigite 1 - CADASTRAR EQUIPAMENTO");
        printf("\n\tDigite 2 - REGISTRAR INCIDENTE");
        printf("\n\tDigite 3 - CONSULTAR EQUIPAMENTO E INCIDENTES");
        printf("\n\tDigite 4 - LISTAR TODOS OS INCIDENTES");
        printf("\n\tDigite 5 - EXCLUIR UM INCIDENTE");
        printf("\n\tDigite 6 - EXCLUIR UM EQUIPAMENTO");
        printf("\n\tDigite 7 - ENCERRAR PROGRAMA");

        printf("\n\n**************************************************************\n");

        scanf("%d", &Opcao);

        switch(Opcao){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                printf("Seu numero e invalido. Digite novamente\n");
                break;
        }
        if (Opcao != 7) {
            printf("\nPressione ENTER para continuar...");
            while (getchar() != '\n');
            getchar();
        }
    }
    while (Opcao != 7);


    return 0;
}
