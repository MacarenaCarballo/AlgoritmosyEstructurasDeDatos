#ifndef PARCIALARBOL_H_INCLUDED
#define PARCIALARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINEA 10
#define ERRORCOD -1
#define REALIZADO 0
#define ES_CARACTER(x) (((x)>='A' && (x)<='Z') || ((x)>='a' && (x)<='z') || ((x)>='0' && (x)<='9'))
#define SIN_MEM -2
#define DUPLICADO -4

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *der;
struct sNodo *izq;}tNodo;

typedef tNodo *tArbol;
typedef int (*tCmp)(void *a, void *b);
typedef void (*tAccion)(void *a, void *b);

void crearArbol(tArbol *pa);
int procesarArchivos(char *nombreArch, tArbol *pa, tCmp comparar);
int insertarEnArbol(tArbol *pa,void *dato, unsigned tam, tCmp comparar);
int eliminarDelArbol(tArbol *pa,void *dato, unsigned tam, tCmp comparar);
void vaciarArbol(tArbol *pa);
unsigned alturaArbol(const tArbol *pa);
tArbol* buscarClave(tArbol*pa,tCmp comparar,void *clave);
void intercambio(tArbol *elim, tArbol *paR);
int compararStrings(void *a, void *b);
void recorrerInOrden(tArbol *pa, tAccion accion, void *parm);
void mostrarString(void *a, void *b);
int aMENOSb(tArbol *pa, tArbol *pb);
void archivoString(void *a, void *b);
#endif // PARCIALARBOL_H_INCLUDED
