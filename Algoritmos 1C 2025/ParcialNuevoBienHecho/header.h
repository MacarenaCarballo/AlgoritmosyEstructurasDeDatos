#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define REALIZADO 0
#define SIN_MEM -1
#define ERROR_COD 1
#define TAM_LOTE 5
#define VACIO 2

typedef struct{
char codLote[TAM_LOTE];
int idProd;
char control[6];}tLote;

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef int (*tCmp)(const void *a, const void *b);

typedef tNodo *tLista;
int leerLote(const char *lote);
int crearLotePrueba(const char *nombreArch);
void mostrarMenu();
int mostrarArchivos(char *titulo, char *nombreArchivo, int porcentaje);
void trozado(char *linea, tLote*reg);
void crearLista(tLista *pl);
void vaciarLista(tLista *pl);
int insertarOrdenado(tLista *pl, tCmp comparar, void *dato, unsigned tam);
int compararId(const void *a, const void *b);
void insertarArchivo(FILE *pf, tLista *pl);
int procesarArchivos(const char *nombreAprobados, const char *nombreObservados, int porcentaje, const char *nombreEntrada);

#endif // HEADER_H_INCLUDED
