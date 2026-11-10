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

void InOrder(NoArv *Pai)
{
    if(Pai -> esq != NULL)
    {
        InOrder(Pai -> esq);
    }

    printf("ID: %d - Equipamento: %d - Gravidade: %d\n", Pai->info.IdIncidente, Pai->info.CodigoEquipamento, Pai->info.gravidade);

    if(Pai -> dir != NULL)
    {
        InOrder(Pai -> dir);
    }
}

NoArv* remover_aux(NoArv *pai, int num)
{
    if(pai == NULL)
    {
        printf("\n \n não encontrado na árvore");
    }
    else
    {
        if(num > pai->info.IdIncidente)
        {
            pai -> dir = remover_aux(pai -> dir,num);
        }
        else
        {
            if(num < pai->info.IdIncidente)
            {
                pai -> esq = remover_aux(pai -> esq,num);
            }
            else
            {
                if(pai -> dir == NULL && pai -> esq == NULL)
                {
                    free(pai);
                    pai = NULL;
                }
                else
                {
                    if (pai->esq==NULL)
                    {
                        NoArv *aux=pai;
                        pai = pai->dir;
                        free(aux);
                    }
                    else
                    {
                        if((pai->dir==NULL))
                        {
                            NoArv *aux=pai;
                            pai = pai->esq;
                            free(aux);
                        }
                        else
                        {
                            NoArv *aux;
                            Incidente temp;
                            aux = pai -> esq;
                            while (aux -> dir != NULL)
                            {
                                aux = aux -> dir;
                            }
                            temp = pai -> info;
                            pai -> info = aux -> info;
                            aux -> info = temp;
                            pai -> esq = remover_aux(pai -> esq,num);
                        }
                    }
                }
            }
        }
    }
    return pai;
}

Arv* remover( Arv *RAIZ, int num)
{
    NoArv *aux = RAIZ -> raiz;
    if(aux -> info.IdIncidente == num && aux -> dir == NULL && aux -> esq == NULL)
    {
        free(aux);
        free(RAIZ);
        return NULL;
    }
    RAIZ -> raiz = remover_aux(RAIZ->raiz,num);
    return RAIZ;
}

void PosOrder(NoArv *Pai)
{
    if(Pai -> dir != NULL)
    {
        PosOrder(Pai -> dir);
    }
    if(Pai -> esq != NULL)
    {
        PosOrder(Pai -> esq);
    }
    free(Pai);
}

void libera(Arv *Arvore)
{
    if(Arvore -> raiz != NULL)
    {
        PosOrder(Arvore -> raiz);
    }
    free(Arvore);
}

#endif
