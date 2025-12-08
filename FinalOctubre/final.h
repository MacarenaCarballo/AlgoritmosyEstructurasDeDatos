#ifndef FINAL_H_INCLUDED
#define FINAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo *sig;
}tNodo;

typedef tNodo *tLista;
typedef int(*tCmp)(const void *,const void*);
typedef void(*tAccion)( void *, void*);

typedef struct
{
    int coeficiente;
    int potencia;
}termino;

void crearLista(tLista *pl);
int insertarOrdenado(tLista *pl,  void *dato, unsigned tam, tCmp comparar, tAccion accion);
int listaLlena(const tLista *pl, unsigned tam);
int listaVacia(const tLista *pl);
void vaciarLista(tLista *pl);
void mapeo(tLista *pl, tAccion accion);
void mostrarLista(void *a, void *b);
int compararPotencia(const void *a,const void *b);
int bajarPolinomio(char *archivo, tLista *lista);
void sumarCoeficientes( void *a,  void *b);
void grabarArchivo(void *a, FILE *pf);
int sumarPolinomios(tLista *p1, tLista *p2,tCmp comparar ,tAccion accion);

#endif // FINAL_H_INCLUDED
