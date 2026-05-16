#ifndef HEADALGORITMOS_H_INCLUDED
#define HEADALGORITMOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ERRORCOD -2
#define REALIZADO 0
#define SIN_MEM -1
#define DUPLICADO -4

typedef int (*tCmp)(void*a, void*b);
typedef int (*tAccion)(void*a, void*b);

typedef struct{
    int dia;
    int mes;
    int anio;
}t_Fecha;
typedef struct
{
    char codProd[7];
    char descrip[26];
    int lote;
    t_Fecha fVto;
    int cant;
}tStock;

typedef struct{
int pos;
char codProd[7];}tIndice;

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo*der;
struct sNodo*izq;}tNodo;

typedef tNodo *tArbol;


int generarLote(char *nombreArch);
int leerLote(char *nombreArch,tArbol *pa,tCmp comparar);
void crearArbol(tArbol *pa);
int insertarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar, tAccion accion, void *param);
int alturaArbol(const tArbol *pa);
void vaciarArbol(tArbol *pa);
int compararCodProd(void *a, void*b);
void recorrerInOrden(tArbol *pa,tAccion accion);
int mostrarCodProd(void *a, void*b);
int crearIndice(void *dato, void *param);
int leerIndice(const char *nombreIndice);
tArbol *buscarClave(tArbol *pa,tCmp comparar, void *clave);
int eliminarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar, tAccion accion, void *param);
int balancear(FILE *pf,int ini ,int fin, tArbol *pa);
int compararNada(void *a, void *b);
#endif // HEADALGORITMOS_H_INCLUDED
