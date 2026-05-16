#ifndef PILAHEAD_H_INCLUDED
#define PILAHEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo *tPila;

void crearPila(tPila *pp);
void vaciarPila(tPila *pp);
int insertarPila(tPila *pp, void *dato, unsigned tam);

#endif // PILAHEAD_H_INCLUDED
