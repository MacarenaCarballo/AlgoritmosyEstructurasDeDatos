#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALIZADO 0
#define ERRORCOD 1
#define MINIMO(x,y) ((x)<(y)? (x):(y))

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct {
    char nombre[50];
    char dni[10];
    float sueldo;
    Fecha fechaIngreso;
} Empleado;

typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo*sig;
} tNodo;

typedef struct
{
    tNodo*pri;
    tNodo*ult;
} tCola;

typedef int (*tCmp)(void*a, void*b);
typedef void (*tAccion)(void*a, void*b);

void crearCola(tCola *pc);
int encolar(tCola *pc, void *dato, unsigned tam);
int desencolar(tCola *pc, void *dato, unsigned tam);
void vaciarCola(tCola *pc);
int procesarArchivoTxt(const char *nombreArch, tCola *pc);
int trozado(char *linea, Empleado* emp);
#endif // HEAD_H_INCLUDED
