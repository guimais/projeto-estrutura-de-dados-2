#ifndef APOIO_H_INCLUDED
#define APOIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int IdIncidente;
    int CodigoEquipamento;
    int gravidade;
} Incidente;

typedef struct NoArvore
{
    Incidente info;
    struct NoArvore *esq;
    struct NoArvore *dir;
}NoArv;

typedef struct BaseArv
{
    NoArv *raiz;
}Arv;

Arv* Criar_Arvore()
{
    Arv *aux;
    aux=(Arv*)malloc(sizeof(Arv));
    aux->raiz = NULL;
    return aux;
}

int ArvVazia(Arv *base)
{
    if(base->raiz==NULL)
    {
        return 1;
    }
    return 0;
}

NoArv* aux_insere(NoArv *no, Incidente num)
{
    int flag;
    NoArv *Pai;
    NoArv *novo = (NoArv*)malloc(sizeof(NoArv));
    novo -> info = num;
    novo -> esq = NULL;
    novo -> dir = NULL;

    if(no == NULL)
    {
        return novo;
    }
    else
    {
        Pai = no;
        flag = 0;
        while (flag == 0)
        {
            if(Pai -> info.IdIncidente < num.IdIncidente)
            {
                if(Pai -> dir == NULL)
                {
                    Pai -> dir = novo;
                    flag = 1;
                }
                else
                {
                    Pai = Pai -> dir;
                }
            }
            else
            {
                if(Pai -> info.IdIncidente > num.IdIncidente)
                {
                    if(Pai -> esq == NULL)
                    {
                        Pai -> esq = novo;
                        flag = 1;
                    }
                    else
                    {
                        Pai = Pai -> esq;
                    }
                }
                else
                {
                    flag = 1;
                    free(novo);
                }
            }
        }
    }
    return no;
}

void insere(Arv *Arvore, Incidente num)
{
    Arvore -> raiz = aux_insere(Arvore -> raiz, num);
}

NoArv* BuscaArv(Arv *Arvore, int num)
{
    int flag;
    NoArv *Pai;
    if(Arvore -> raiz ==NULL)
    {
        return NULL;
    }
    else
    {
        Pai = Arvore -> raiz;
        flag = 0;
        while (flag == 0)
        {
            if(num > Pai -> info.IdIncidente)
            {
                if(Pai -> dir == NULL)
                {
                    flag = 2;
                }
                else
                {
                    Pai = Pai -> dir;
                }
            }
            else
            {
                if(num < Pai -> info.IdIncidente)
                {
                    if(Pai -> esq == NULL)
                    {
                        flag = 2;
                    }
                    else
                    {
                        Pai = Pai -> esq;
                    }
                }
                else
                {
                    flag = 1;
                }
            }
        }
    }
    if(flag == 1)
    {
        return Pai;
    }
    return NULL;
}

#endif
