#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SATISFACTORIO 0
#define SIN_MEM -1
#define DUPLICADO -2

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *der;
struct sNodo *izq;}tNodo;

typedef tNodo *tArbol;


typedef int(*tCmp)(void *a, void *b);
typedef void(*tAccion)(void *a, void *parms);


void crearArbol(tArbol *p);
int insertarArbolI(tArbol* p, void* dato, unsigned tam,tCmp cmp,tAccion accion);
int compararEnteros(void *a, void *b);
int insertarArbolR(tArbol* pa, void* dato, unsigned tam,tCmp cmp,tAccion accion);
void imprimirEnteros(void *dato, void *param);
void recorrerPreorden(tArbol* pa, tAccion accion, void* param);
void recorrerInorden(tArbol* pa, tAccion accion,void* param);
void recorrerPostorden(tArbol* pa, tAccion accion, void* param);
int contarNodos(const tArbol *pa);
int contarNohoja(const tArbol* pa);
int contarHojas(const tArbol* pa);
unsigned alturaArbol(const tArbol* pa);
int contarNodosConIzq(const tArbol* pa);
unsigned cantNodosNivel(const tArbol *pa, unsigned nivel);
unsigned cantNodosHastaNivel(const tArbol *pa, unsigned nivel);
unsigned cantNodosDesdeNivel(const tArbol *pa, unsigned nivel);
unsigned buscarClave(const tArbol *pa, tCmp comparar,void *clave);
unsigned cantNodosPorClaveDer(const tArbol *pa, tCmp comparar,void *clave);
int eliminarHoja(tArbol *pa, tCmp comparar,void *clave);
int eliminarTodasHoja(tArbol *pa);
tArbol* buscarClave2(tArbol*pa,tCmp comparar,void *clave);
void intercambio(tArbol *elim, tArbol *paR);
int eliminarDelArbol(tArbol *pa,void *dato, unsigned tam, tCmp comparar);

void vaciarArbol(tArbol* pa);
#endif // HEAD_H_INCLUDED
