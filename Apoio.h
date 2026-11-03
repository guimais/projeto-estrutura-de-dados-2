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

typedef struct noArv {
    Incidente info;
    struct noArv *esq;
    struct noArv *dir;
} NoArv;

typedef struct arvore {
    NoArv *raiz;
} Arvore;

Arvore* CriaArvore()
{
    Arvore *aux;
    aux = (Arvore *)malloc(sizeof(Arvore));
    aux->raiz = NULL;
    return aux;
}

#endif
