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

typedef struct EstruturaTabela
{
    NoTabela *vetor[TAMANHO_TABELA];
}Tabela;


Tabela* Criar_Tabela()
{
    Tabela *aux;
    aux = (Tabela*)malloc(sizeof(Tabela));
    for(int i = 0; i < TAMANHO_TABELA; i++)
    {
        aux->vetor[i] = NULL;
    }
    return aux;
}

int FuncaoHash(int codigo)
{
    return codigo % TAMANHO_TABELA;
}

NoTabela* BuscaNaTabela(Tabela *TabelaHash, int codigo)
{
    int flag, posicao;
    NoTabela *aux;
    posicao = FuncaoHash(codigo);
    aux = TabelaHash -> vetor[posicao];
    flag = 0;
    while (aux != NULL && flag == 0)
    {
        if(aux -> info.CodigoEquipamento == codigo)
        {
            flag = 1;
        }
        else
        {
            aux = aux -> prox;
        }
    }
    if(flag == 1)
    {
        return aux;
    }
    return NULL;
}

void InsereNaTabela(Tabela *TabelaHash, Equipamento equipamento)
{
    int posicao;
    NoTabela *novo = (NoTabela*)malloc(sizeof(NoTabela));
    novo -> info = equipamento;
    novo -> incidentes = NULL;
    novo -> prox = NULL;

    if(BuscaNaTabela(TabelaHash, equipamento.CodigoEquipamento) != NULL)
    {
        free(novo);
    }
    else
    {
        posicao = FuncaoHash(equipamento.CodigoEquipamento);
        novo -> prox = TabelaHash -> vetor[posicao];
        TabelaHash -> vetor[posicao] = novo;
    }
}

#endif
