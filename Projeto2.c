#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Apoio.h"
#include "TabelaHash.h"

int main()
{
    Arv *Arvore = Criar_Arvore();
    NoTabela *TabelaHash[TAMANHO_TABELA];

    int Opcao, valor, codigo, i;
    char nome[100], entrada[100];

    Incidente novoIncidente;
    Equipamento novoEquipamento;

    NoArv *incidente;
    NoTabela *equip;
    NoLista *lista;

    for(i = 0; i < TAMANHO_TABELA; i++)
    {
        TabelaHash[i] = NULL;
    }

    do
    {
        system("cls");
        printf("\n**************************************************************");
        printf("\n Sistema de Gerenciamento de Falhas em Equipamentos");

        printf("\n\n\tDigite 1 - CADASTRAR EQUIPAMENTO");
        printf("\n\tDigite 2 - REGISTRAR INCIDENTE");
        printf("\n\tDigite 3 - CONSULTAR EQUIPAMENTO E INCIDENTES");
        printf("\n\tDigite 4 - LISTAR TODOS OS INCIDENTES");
        printf("\n\tDigite 5 - EXCLUIR UM INCIDENTE");
        printf("\n\tDigite 6 - EXCLUIR UM EQUIPAMENTO");
        printf("\n\tDigite 7 - ENCERRAR PROGRAMA");

        printf("\n\n**************************************************************\n");

        Opcao = 0;
        scanf("%d", &Opcao);

        switch(Opcao)
        {
            case 1:
                printf("Digite o codigo do equipamento: ");
                valor = 0;
                scanf("%d", &valor);

                if(valor < 1000 || valor > 9999)
                {
                    printf("Codigo invalido. Use 4 digitos (1000 a 9999).\n");
                }
                else
                {
                    if(BuscaTabela(TabelaHash, valor) != NULL)
                    {
                        printf("Equipamento %d ja cadastrado.\n", valor);
                    }
                    else
                    {
                        printf("Digite o nome do equipamento (ate 10 caracteres): ");
                        scanf("%99s", nome);

                        if(strlen(nome) > 10)
                        {
                            printf("Nome invalido. Use no maximo 10 caracteres.\n");
                        }
                        else
                        {
                            novoEquipamento.CodigoEquipamento = valor;
                            strcpy(novoEquipamento.Nome, nome);
                            insere_tabela(TabelaHash, novoEquipamento);
                            printf("Equipamento %d cadastrado.\n", valor);
                        }
                    }
                }
                break;
            case 2:
                printf("Digite o ID do incidente: ");
                valor = 0;
                scanf("%d", &valor);

                if(valor < 10 || valor > 99)
                {
                    printf("ID invalido. Use 2 digitos.\n");
                }
                else
                {
                    if(BuscaArv(Arvore, valor) != NULL)
                    {
                        printf("ID %d ja cadastrado.\n", valor);
                    }
                    else
                    {
                        novoIncidente.IdIncidente = valor;

                        printf("Digite o codigo do equipamento: ");
                        novoIncidente.CodigoEquipamento = 0;
                        scanf("%d", &novoIncidente.CodigoEquipamento);

                        if(novoIncidente.CodigoEquipamento < 1000 || novoIncidente.CodigoEquipamento > 9999)
                        {
                            printf("Codigo invalido. Use 4 digitos (1000 a 9999).\n");
                        }
                        else
                        {
                            equip = BuscaTabela(TabelaHash, novoIncidente.CodigoEquipamento);
                            if(equip == NULL)
                            {
                                printf("Equipamento %d nao cadastrado.\n", novoIncidente.CodigoEquipamento);
                            }
                            else
                            {
                                printf("Digite a gravidade (1-Baixa, 2-Media, 3-Alta): ");
                                novoIncidente.gravidade = 0;
                                scanf("%d", &novoIncidente.gravidade);

                                if(novoIncidente.gravidade < 1 || novoIncidente.gravidade > 3)
                                {
                                    printf("Gravidade invalida.\n");
                                }
                                else
                                {
                                    insere(Arvore, novoIncidente);
                                    insere_lista(equip, valor);
                                    printf("Incidente %d registrado.\n", valor);
                                }
                            }
                        }
                    }
                }
                break;
            case 3:
                printf("Digite o codigo do equipamento: ");
                valor = 0;
                scanf("%d", &valor);

                if(valor < 1000 || valor > 9999)
                {
                    printf("Codigo invalido. Use 4 digitos (1000 a 9999).\n");
                }
                else
                {
                    equip = BuscaTabela(TabelaHash, valor);
                    if(equip == NULL)
                    {
                        printf("Equipamento %d nao encontrado.\n", valor);
                    }
                    else
                    {
                        printf("Codigo: %d - Nome: %s\n", equip -> info.CodigoEquipamento, equip -> info.Nome);
                        if(equip -> incidentes == NULL)
                        {
                            printf("Nenhum incidente associado.\n");
                        }
                        else
                        {
                            printf("Incidentes:\n");
                            lista = equip -> incidentes;
                            while(lista != NULL)
                            {
                                incidente = BuscaArv(Arvore, lista -> IdIncidente);
                                if(incidente != NULL)
                                {
                                    printf("ID: %d - Gravidade: %d\n", incidente -> info.IdIncidente, incidente -> info.gravidade);
                                }
                                lista = lista -> prox;
                            }
                        }
                    }
                }
                break;
            case 4:
                if(ArvVazia(Arvore) == 1)
                {
                    printf("Nenhum incidente cadastrado.\n");
                }
                else
                {
                    InOrder(Arvore -> raiz);
                }
                break;
            case 5:
                if(ArvVazia(Arvore) == 1)
                {
                    printf("Nenhum incidente cadastrado.\n");
                }
                else
                {
                    printf("Digite o ID do incidente: ");
                    valor = 0;
                    scanf("%d", &valor);

                    incidente = BuscaArv(Arvore, valor);
                    if(incidente == NULL)
                    {
                        printf("ID %d nao encontrado.\n", valor);
                    }
                    else
                    {
                        codigo = incidente -> info.CodigoEquipamento;
                        Arvore = remover(Arvore, valor);
                        if(Arvore == NULL)
                        {
                            Arvore = Criar_Arvore();
                        }
                        equip = BuscaTabela(TabelaHash, codigo);
                        if(equip != NULL)
                        {
                            remover_lista(equip, valor);
                        }
                        printf("Incidente %d removido.\n", valor);
                    }
                }
                break;
            case 6:
                printf("Digite o codigo do equipamento: ");
                valor = 0;
                scanf("%d", &valor);

                if(valor < 1000 || valor > 9999)
                {
                    printf("Codigo invalido. Use 4 digitos (1000 a 9999).\n");
                }
                else
                {
                    equip = BuscaTabela(TabelaHash, valor);
                    if(equip == NULL)
                    {
                        printf("Equipamento %d nao encontrado.\n", valor);
                    }
                    else
                    {
                        lista = equip -> incidentes;
                        while(lista != NULL)
                        {
                            Arvore = remover(Arvore, lista -> IdIncidente);
                            if(Arvore == NULL)
                            {
                                Arvore = Criar_Arvore();
                            }
                            lista = lista -> prox;
                        }
                        remover_tabela(TabelaHash, valor);
                        printf("Equipamento %d e seus incidentes removidos.\n", valor);
                    }
                }
                break;
            case 7:
                libera(Arvore);
                libera_tabela(TabelaHash);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Seu numero e invalido. Digite novamente\n");
                break;
        }
        if(Opcao != 7)
        {
            fgets(entrada, 100, stdin);
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    }
    while(Opcao != 7);

    return 0;
}
