#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 11
#define PILA_LLENA 1
#define PILA_VACIA 2
#define PILA_NO_VACIA 0
#define PILA_DISPONIBLE 0
#define SATISFACTORIO 0
#define MINIMO(x, y) ((x) <= (y) ? (x) : (y))

typedef struct {
char pila[TAM];
int tope;}tPila;

void crearPila(tPila* pila);
//dato que no modifico y generico por es CONST VOID
//Paso el tipo de dato por copia ya que me ahorro  bytes
int apilar(tPila *pila,const void *dato, unsigned tam);
int desapilar(tPila *pila, void * dato, unsigned tam);
void vaciarPila(tPila *pila);
int verTope(const tPila *pila, void *dato, unsigned tam);
int pilaLlena(const tPila *pila, unsigned tam);
int pilaVacia(const tPila *pila);
int mi_Strlen(const char *dato);
#endif // FUNCIONES_H_INCLUDED
