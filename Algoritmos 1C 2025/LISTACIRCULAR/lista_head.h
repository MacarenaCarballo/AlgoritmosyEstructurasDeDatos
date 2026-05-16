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
int listaLlena(const tLista *lista,unsigned tam);
int listaVacia(const tLista *lista);
int agregarNodo(tLista *lista, const void *dato, unsigned tam);
int eliminarNodo(tLista *lista, void *dato, unsigned tam);
void vaciarLista(tLista *lista);
int agegarAPila(tLista *lista, const void *dato, unsigned tam);
int agegarACola(tLista *lista, const void *dato, unsigned tam);
void mostrarEntero(void *dato, void *nada);
int mapLista(tLista *lista, Funcion accion);


#endif // LISTA_HEAD_H_INCLUDED
