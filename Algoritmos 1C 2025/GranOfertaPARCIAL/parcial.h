#ifndef PARCIAL_H_INCLUDED
#define PARCIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ERRORCOD -2
#define REALIZADO 0
#define SIN_MEM -1
typedef int (*tCmp)(void*a, void*b);
typedef void (*tAccion)(void*a, void*b);

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

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo *tLista;

int generarLote(char *nombreArch);
int leerLote(char *nombreArch);
void obtenerFecha(t_Fecha *act);
void crearLista(tLista *pl);
int insertarEnOrden(tLista *pl, void *dato, unsigned tam,tCmp comparar);
void vaciarLista(tLista *pl);
int compararEnteros(void *a, void *b);
void mostrarEntero(void *a, void *b);
int mapeo(tLista *pl, tAccion accion, void *param);
void mostrarStock(void *a, void *b);
int bajarArchivo(char *nombreArch,tCmp comparar, tLista *pl, tAccion accion);
int compararFechas(void *a, void *b);
int productosAVencer(tLista *pl,tAccion accion,t_Fecha act);
void generarStock(void *a, void *b);
int contarDias(int dia, int mes, int anio);
void mostrarMasproximo(tLista*pl);
#endif // PARCIAL_H_INCLUDED
