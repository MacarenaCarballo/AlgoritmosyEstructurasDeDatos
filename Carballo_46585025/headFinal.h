#ifndef HEADFINAL_H_INCLUDED
#define HEADFINAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 1
#define HECHO 0

typedef int(*tCmp)(const void*a,const void*b);
typedef void(*tAccion)(void*a, void*b);

typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo*der;
    struct sNodo*izq;
}tNodo;

typedef tNodo *tArbol;

void crearArbol(tArbol *pa);
int insertarEnOrden(tArbol *pa, const void *dato, unsigned tam, tCmp comparar);
void vaciarArbol(tArbol *pa);
int compararEnteros(const void *a, const void *b);
void recorrerPreOrden(const tArbol *pa, tAccion mostrar, void *param);
void mostrarEntero(void *a, void *b);
int buscarSegundoMenor(const tArbol *pa, tCmp comparar);
int menorBuscar(tArbol *pa,tAccion comparar);

#endif // HEADFINAL_H_INCLUDED
