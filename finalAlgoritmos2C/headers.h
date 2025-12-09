#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0


typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo* sig;
}tNodo;

typedef  tNodo * t_lista;

typedef struct{
char iniciales[4];
unsigned puntaje;
}t_puntaje;

typedef struct{
t_lista tabla;
unsigned tam;
}t_tabla_puntos;

typedef int(*tCmp)(const void *a,const void*b);
typedef void(*tAccion)(const void *a, void*b);

void crearLista(t_lista *pl);
int insertarNodo(t_lista *pl,const void *dato, unsigned tam, tCmp comparar,unsigned top);
void vaciarLista(t_lista *pl);
int listaLlena(t_lista *pl, unsigned tam);
int listaVacia(t_lista *pl);
int compararEnteros(const void *a,const void *b);
int tablaPuntaje(char *nombre, t_tabla_puntos *tabla);
void crear_tabla_puntos(t_tabla_puntos* p, unsigned tam);
int agregar_puntaje(t_tabla_puntos* p, const t_puntaje* dato);
void imprimir_tabla_puntos(t_tabla_puntos* p);
void vaciar_tabla_puntos(t_tabla_puntos* p);
void mostrarEntero(const void *dato, void *b);
int mostrarLista(t_lista *lista, tAccion mostrarDato);
#endif // HEADERS_H_INCLUDED
