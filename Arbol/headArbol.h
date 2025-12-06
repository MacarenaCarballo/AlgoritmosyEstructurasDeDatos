#ifndef HEADARBOL_H_INCLUDED
#define HEADARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MINIMO(x,y) ((x)<(y)?x:y)
#define MAXIMO(x,y) ((x)>(y)?x:y)
typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo *izq;
    struct sNodo *der;
}tNodo;

typedef tNodo *tArbol;
typedef int(*tCmp)(const void *,const void*);
typedef void(*tAccion)( void *, void*);

void crearArbol(tArbol *pa);
int insertarOrdenado(tArbol *pa, void *dato,unsigned tam, tCmp comparar);
int eliminarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar);
int arbolVacio(const tArbol *pa);
int arbolLleno(const tArbol *pa,unsigned tam);
void vaciarArbol(tArbol *pa);
int contarNodos(const tArbol *pa);
int alturaArbol(const tArbol *pa);
void recorrerPreorden(const tArbol *pa,tAccion accion);
int compararCaracteres(const void *a, const void *b);
void mostrarLista(void *a, void *b);
tArbol* buscarClave( tArbol *pa, tCmp comparar,void *clave);
void intercambio(tArbol *elim, tArbol *paR);
#endif // HEADARBOL_H_INCLUDED
