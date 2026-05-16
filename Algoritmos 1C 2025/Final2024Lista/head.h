#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned codMat;
    char codCursada[7];
    unsigned notaFinal;
} tMateria;

typedef struct
{
    unsigned dni;
    char apellido[21];
    char nombre[21];
    char codCarrera[4];
    tMateria materia;
} tAlumno;

typedef struct sNodo{
void *dato;
unsigned tam;
struct sNodo *sig;}tNodo;

typedef tNodo *tLista;

typedef int(*tCmp)(void *a, void *b);
typedef void(*tAccion)(void *a, void *b);

int crearLote(char *lote);
void crearLista(tLista *pl);
void vaciarLista(tLista *pl);
int insertarAlPrincipio(tLista *pl, void *dato, unsigned tam);
int cargarAlista(tLista *pl, char *nombre);
void trozado(char *linea, tAlumno *info);
int cargarAlista(tLista *pl, char *nombre);
void mapeo(tLista *pl,tAccion accion);
void mostrarLista(void *a, void *b);
void mostrarAlreves(tLista *pl, tAccion accion);
tLista *buscarMenor(tLista *pl, tCmp comparar);
int compararDNI(void *a, void *b);
int ordenamientoSeleccion(tLista *pl, tCmp comparar);
int compararApeNomDni(void *a, void *b);
#endif // HEAD_H_INCLUDED
