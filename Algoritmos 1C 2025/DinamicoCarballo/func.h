#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_MEM -1
#define REALIZADO 0
#define PILA_DISPO 0
#define PILA_NO_VACIA 0
#define PILA_LLENA 2
#define PILA_VACIA 1
#define MINIMO(x,y) ((x)<(y)? (x):(y))

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo* tPila;

void crearPila(tPila* pila);
int apilar(tPila *pila, void *dato, unsigned tam);
int desapilar(tPila *pila, void* dato, unsigned tam);
int pilaVacia(const tPila *pila);
int pilaLlena(const tPila *pila, unsigned tam);
void vaciarPila(tPila *pila);
int verTope(tPila *pila, void *dato, unsigned tam);

#endif // FUNC_H_INCLUDED
