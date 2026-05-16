#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_head.h"

#define SIN_MEM -1
#define REALIZADO 0
#define PILA_DISPO 0
#define PILA_NO_VACIA 0
#define PILA_LLENA 2
#define PILA_VACIA 1
#define MINIMO(x,y) ((x)<(y)? (x):(y))


void crearPila(tLista* pila);
int apilar(tLista *pila, void *dato, unsigned tam);
int desapilar(tLista *pila, void* dato, unsigned tam);
int pilaVacia(const tLista *pila);
int pilaLlena(const tLista *pila, unsigned tam);
void vaciarPila(tLista *pila);
int verTope(tLista *pila, void *dato, unsigned tam);

#endif // PILADINAMICA_H_INCLUDED
