#ifndef HEADARBOL_H_INCLUDED
#define HEADARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int clave;
    int noClave;
} tDato;

typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo *der;
    struct sNodo *izq;
} tNodo;

typedef tNodo *tArbol;
typedef int (*tCmp)(const void *a, const void *b);
typedef void (*tAccion)( void *a, const void *b);

void crearArbol(tArbol *pa);
int insertarR(tArbol *pa,const void *dato, unsigned tam, tCmp comparar);
void vaciarArbol(tArbol *pa);
int bajarArchivo(char *archivo, tArbol *pa);
void recorrerInOrden(tArbol *pa, tAccion accion);
void mostrar( void *a, const void *b);
int contarocurrencias(tArbol *pa,const void *dato, tCmp comparar);
void espejarArbol(tArbol *pa);
int compararClave(const void *a,const void *b);
int compararNoclave(const void *a,const void *b);

#endif // HEADARBOL_H_INCLUDED
