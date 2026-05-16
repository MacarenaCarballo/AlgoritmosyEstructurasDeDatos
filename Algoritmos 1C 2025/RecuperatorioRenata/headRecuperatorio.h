#ifndef HEADRECUPERATORIO_H_INCLUDED
#define HEADRECUPERATORIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo* der;
    struct sNodo*izq;
}tNodo;

typedef tNodo* tArbol;

typedef struct {
int clave;
int dato;}tInfo;

typedef int (*tCmp)(void *a, void*b);
typedef void (*tAccion)(void *a, void*b);

void crearArbol(tArbol *pa);
void vaciarArbol(tArbol *pa);
int insertarEnArbol(tArbol *pa, void *dato, unsigned tam, tCmp comparar);
void recorrerInOrden(tArbol *pa, tAccion accion);
int cargarArbol(tArbol *pa, char *nombre);
int crearLote(char *lote);
int contarOcurrencias(tArbol *pa, tCmp comparar, void *datoNoClave);
void mostrarArbol(void *a, void *b);
int compararClave(void *a, void *b);
void trozado(char *linea, tInfo *reg);
int compararDato(void *a, void *b);
void espejarArbol(tArbol *pa);
#endif // HEADRECUPERATORIO_H_INCLUDED
