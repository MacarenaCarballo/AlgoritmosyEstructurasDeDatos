#ifndef PILA_HIBRIDA_H_INCLUDED
#define PILA_HIBRIDA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TAM_PILA 12

#define PILA_LLENA   -1
#define TODO_OK       1
#define PILA_VACIA   -2
#define SIN_MEM      -3
#define MIN(a,b) (a) < (b)? (a) : (b)

typedef struct {
    void *dato;
    size_t tam;
} t_Info;


typedef struct {
    t_Info *elementos[TAM_PILA];
    int tope;
} t_Pila;

void crearPila(t_Pila* pila);
int apilar(t_Pila *pila,const void *dato, unsigned tam);
int desapilar(t_Pila *pila, void * dato, unsigned tam);
void vaciarPila(t_Pila *pila);
int verTope(const t_Pila *pila, void *dato, unsigned tam);
int pilaLlena(const t_Pila *pila);
int pilaVacia(const t_Pila *pila);

#endif
