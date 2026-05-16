#ifndef HEADERFINAL_H_INCLUDED
#define HEADERFINAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MINIMO(x,y) x<y?x:y

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo *tPila;
typedef int(*tCmp)(void*a, void*b);

void crearPila(tPila *pp);
int verTope(tPila *pp, void *dato, unsigned tam);
void vaciarPila(tPila *pp);
int apilar(tPila *pp, void *dato, unsigned tam);
int desapilar(tPila *pp, void *dato, unsigned tam);
int pilaVacia(tPila *pp, void *dato, unsigned tam);
int validarXML(char *archivo);
int validarXMLExtenso(char *archivo, char *version);

#endif // HEADERFINAL_H_INCLUDED
