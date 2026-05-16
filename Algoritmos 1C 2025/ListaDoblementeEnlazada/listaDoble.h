#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUPLICADO -1
#define SIN_MEM -2
#define REALIZADO 0
#define NO_ENCONTRADO -3
#define MINIMO(x,y) (x)<(y)? (x):(y)

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo* sig;
struct sNodo* ant;}tNodo;

typedef tNodo *tLista;
typedef int (*tComparar)( void *info1, void *info2);
typedef void (*Funcion)(void *dato, void *dato2);
typedef int (*tFiltro)(void *dato, void *param);

void crearLista(tLista *lista);
int insertarNodo(tLista *lista, void * dato, unsigned tam, tComparar comparar,Funcion accion, void *arg);
int compararEnteros(void *dato1, void *dato2);
void vaciarLista(tLista *lista);
int listaLlena(tLista *lista, unsigned tam);
int listaVacia(tLista *lista);
int mostrarListaFinal(tLista *lista, Funcion accion);
int mostrarListaPrincipio(tLista *lista, Funcion accion);
void mostrarEntero(void *dato, void *dato2);
int eliminarNodo(tLista *lista, void * dato, unsigned tam, tComparar comparar);
int filter(tLista *lista,tFiltro filtro, void *param);
int borrarPares(void *dato, void *param);

#endif // LISTADOBLE_H_INCLUDED
