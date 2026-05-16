#ifndef HEADER_CARBALLO_H_INCLUDED
#define HEADER_CARBALLO_H_INCLUDED

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

typedef int(*tCmp)(const void *a ,const void *b);
typedef void(*tAccion)(void *a , void *b);

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo *tLista;

int crearLotePrueba(const char *nombreArch);
int insertarOrdenado(tLista *pl, void *dato, unsigned tam, tCmp comparar);
int leerLote(const char *lote, tLista *pl);
void crearLista(tLista *pl);
int listaLlena(const tLista *pl);
void vaciarLista(tLista *pl);
int listaVacia(const tLista *pl);
int comparoControl(const void *a, const void *b);
int comparoLote(const void *a, const void *b);
void mostrarLote(void *a, void *b);
int mapeo(tLista *pl, tAccion accion, void *dato);
void mostrarMenu();
int procesarArchivos(tLista *pl, tCmp comparar, char* archO, char *archA, int porcentaje, tCmp compararControl, tCmp compararIdProd);
void insertarArchivo(FILE *pf, tLista *pl);
void trozado(char *linea, tLote*reg);
int mostrarArchivos(char *titulo, char *nombreArchivo, int porcentaje);
int comparoTodoOK(const void *a, const void *b);

#endif // HEADER_CARBALLO_H_INCLUDED
