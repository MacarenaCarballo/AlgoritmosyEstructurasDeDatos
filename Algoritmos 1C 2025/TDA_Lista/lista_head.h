#ifndef LISTA_HEAD_H_INCLUDED
#define LISTA_HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_MEM -1
#define REALIZADO 0
#define LISTA_DISPO 0
#define LISTA_NO_VACIA 0
#define LISTA_LLENA 1
#define LISTA_VACIA 1
#define MINIMO(x,y) ((x)<(y)? (x):(y))
#define DUPLICADO -1

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo* tLista;

typedef void (*Mostrar)(const void *dato);
typedef void (*Funcion)(void *dato, void *valor);
typedef int (*tComparar)(const void *info1,const void *info2);

void crearLista(tLista* lista);
int mostrarLista(tLista *lista, Mostrar mostrarDato);
int ponerAlComienzo(tLista *lista, void *dato, unsigned tam);
int listaLlena(const tLista *lista,unsigned tam);
int listaVacia(const tLista *lista);
int insertarEnOrden(tLista *pLista,const void *dato, unsigned tam,tComparar cmp, int duplicado,Funcion accion);
void vaciarLista(tLista *lista);
void mostrarEntero(const void *dato);
int mapV2(tLista *lista,Funcion accion);
void multiplicarPor3(void *dato, void *valor);
void alCuadrado(void *dato, void *valor);
int compararEnteros(const void * info1,const void *info2);
int eliminarNodoSinDuplicadosOrdenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp);
int eliminarNodoSinDuplicadosDesordenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp);
void mostrarChar(const void *dato);
int compararLetras(const void * info1,const void *info2);
int eliminarNodoDuplicadosOrdenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp);
int eliminarNodoDuplicadosDesordenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp);
int ordenarLista(tLista *pLista,tComparar cmp);
void intercambiarNodos(tNodo *nodo1, tNodo *nodo2);
void mostrarListaInversa(tLista* lista, Mostrar mostrarDato);
void mostrarListaInversaItera(tLista* lista, Mostrar mostrarDato, unsigned tam);
int ordenamientoDeNodos(tLista *pLista,tComparar cmp);
tLista*  buscarMenor(tLista *pLista,tComparar cmp);

#endif // LISTA_HEAD_H_INCLUDED
