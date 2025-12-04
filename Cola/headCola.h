#ifndef HEADCOLA_H_INCLUDED
#define HEADCOLA_H_INCLUDED

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

typedef struct
{
    tNodo *pri;
    tNodo *ult;
}tCola;

void crearCola(tCola *cola);
int ponerEnCola(tCola *cola,const void* dato,unsigned tam);
int sacarDeCola(tCola *cola,void* dato,unsigned tam);
int verPrimero(const tCola *cola,void* dato,unsigned tam);
void vaciarCola(tCola *cola);
int colaVacia(const tCola *cola);
int colaLlena(const tCola *cola, unsigned tam);

#endif // HEADCOLA_H_INCLUDED
