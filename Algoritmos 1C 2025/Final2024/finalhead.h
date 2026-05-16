#ifndef FINALHEAD_H_INCLUDED
#define FINALHEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*tCmp)(void *a, void *b);
typedef void (*tAccion)(void *a, void *b);

typedef struct{
    char clave[6];
    int info;
}tInfo;

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *der;
struct sNodo *izq;}tNodo;

typedef tNodo *tArbol;
void crearArbol(tArbol *pa);
int insertarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar);
int crearLote(char *nombre);
void preOrden(tArbol *pa, tAccion accion, void* param);
void vaciarArbol(tArbol *pa);
void trozar(tInfo *inf, char *linea);
void mostrarArbol(void *dato, void*param);
int bajarArchivo(char *nombre, tArbol *pa);
int compararStrings(void *a, void *b);
int contarCantNodosPorNivel(tArbol *pa, int nivel);
int alturaArbol(tArbol *pa);
int potencia2(int nivel);
int esCompleto(tArbol *pa, int nivel);
#endif // FINALHEAD_H_INCLUDED
