#ifndef HEADLISTA_H_INCLUDED
#define HEADLISTA_H_INCLUDED

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

typedef tNodo *tLista;
typedef int(*tCmp)(const void *,const void*);
typedef void(*tAccion)( void *, void*);

void crearLista(tLista *pl);
int insertarOrdenado(tLista *pl, const void *dato, unsigned tam, tCmp comparar);
int sacarLista(tLista *pl, void *dato, unsigned tam, tCmp comparar);
int listaLlena(const tLista *pl, unsigned tam);
int listaVacia(const tLista *pl);
void vaciarLista(tLista *pl);
int compararCaracteres(const void *a, const void *b);
void mapeo(tLista *pl, tAccion accion);
void mostrarLista(void *a, void *b);

#endif // HEADLISTA_H_INCLUDED
