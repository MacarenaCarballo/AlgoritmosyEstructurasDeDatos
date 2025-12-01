#ifndef HEADPILA_H_INCLUDED
#define HEADPILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMO(x,y) ((x)<(y)?x:y)
typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tPila;
typedef int(*tCmp)(void *,void*);

void crearPila(tPila *p);
void vaciarPila(tPila *p);
int apilar(tPila *p, void *dato, unsigned tam);
int desapilar(tPila *p, void *dato, unsigned tam);
int verTope(tPila *p, void *dato, unsigned tam);
int pilaLlena(tPila *p, unsigned tam);
int pilaVacia(tPila *p);
#endif // HEADPILA_H_INCLUDED
