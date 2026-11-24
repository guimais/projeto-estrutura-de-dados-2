#ifndef TABELAHASH_H_INCLUDED
#define TABELAHASH_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_TABELA 71

typedef struct {
    int CodigoEquipamento;
    char Nome[11];
} Equipamento;

typedef struct NoLista
{
    int IdIncidente;
    struct NoLista *prox;
}NoLista;

typedef struct NoTabela
{
    Equipamento info;
    NoLista *incidentes;
    struct NoTabela *prox;
}NoTabela;

typedef struct BaseTabela
{
    NoTabela *vetor[TAMANHO_TABELA];
}Tabela;


Tabela* Criar_Tabela()
{
    Tabela *aux;
    int i;
    aux = (Tabela*)malloc(sizeof(Tabela));
    for(i = 0; i < TAMANHO_TABELA; i++)
    {
        aux->vetor[i] = NULL;
    }
    return aux;
}

int FuncaoHash(int num)
{
    return num % TAMANHO_TABELA;
}

NoTabela* BuscaTabela(Tabela *TabelaHash, int num)
{
    int flag, posicao;
    NoTabela *aux;
    posicao = FuncaoHash(num);
    if(TabelaHash -> vetor[posicao] == NULL)
    {
        return NULL;
    }
    else
    {
        aux = TabelaHash -> vetor[posicao];
        flag = 0;
        while (flag == 0)
        {
            if(aux -> info.CodigoEquipamento == num)
            {
                flag = 1;
            }
            else
            {
                if(aux -> prox == NULL)
                {
                    flag = 2;
                }
                else
                {
                    aux = aux -> prox;
                }
            }
        }
    }
    if(flag == 1)
    {
        return aux;
    }
    return NULL;
}

void insere_tabela(Tabela *TabelaHash, Equipamento num)
{
    int posicao;
    NoTabela *novo = (NoTabela*)malloc(sizeof(NoTabela));
    novo -> info = num;
    novo -> incidentes = NULL;
    novo -> prox = NULL;

    if(BuscaTabela(TabelaHash, num.CodigoEquipamento) != NULL)
    {
        free(novo);
    }
    else
    {
        posicao = FuncaoHash(num.CodigoEquipamento);
        novo -> prox = TabelaHash -> vetor[posicao];
        TabelaHash -> vetor[posicao] = novo;
    }
}

void insere_lista(NoTabela *equipamento, int num)
{
    NoLista *novo = (NoLista*)malloc(sizeof(NoLista));
    novo -> IdIncidente = num;
    novo -> prox = equipamento -> incidentes;
    equipamento -> incidentes = novo;
}

void remover_lista(NoTabela *equipamento, int num)
{
    int flag;
    NoLista *aux;
    NoLista *anterior;
    if(equipamento -> incidentes != NULL)
    {
        aux = equipamento -> incidentes;
        anterior = NULL;
        flag = 0;
        while (flag == 0)
        {
            if(aux -> IdIncidente == num)
            {
                flag = 1;
            }
            else
            {
                if(aux -> prox == NULL)
                {
                    flag = 2;
                }
                else
                {
                    anterior = aux;
                    aux = aux -> prox;
                }
            }
        }
        if(flag == 1)
        {
            if(anterior == NULL)
            {
                equipamento -> incidentes = aux -> prox;
            }
            else
            {
                anterior -> prox = aux -> prox;
            }
            free(aux);
        }
    }
}

void libera_lista(NoLista *inicio)
{
    NoLista *aux;
    NoLista *temp;
    aux = inicio;
    while(aux != NULL)
    {
        temp = aux;
        aux = aux -> prox;
        free(temp);
    }
}

void libera_tabela(Tabela *TabelaHash)
{
    int i;
    NoTabela *aux;
    NoTabela *temp;
    for(i = 0; i < TAMANHO_TABELA; i++)
    {
        aux = TabelaHash -> vetor[i];
        while(aux != NULL)
        {
            temp = aux;
            aux = aux -> prox;
            libera_lista(temp -> incidentes);
            free(temp);
        }
    }
    free(TabelaHash);
}

#endif
