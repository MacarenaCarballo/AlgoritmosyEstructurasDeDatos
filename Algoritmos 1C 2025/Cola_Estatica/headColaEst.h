#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_COLA 20
#define MINIMO(x,y) ((x)<(y)? (x):(y));
#define COLA_LLENA 1
#define COLA_VACIA 2
#define COLA_NO_VACIA 3
#define COLA_DISPONIBLE 4
#define REALIZADO 0
#define TAM_CHAR 10
typedef struct{
char cola[TAM_COLA];
unsigned pri;
unsigned ult;
unsigned tam_disp;}tCola;

typedef struct
{
    char codLote[TAM_CHAR];
    char idProd [TAM_CHAR];
    char resulControl[TAM_CHAR];
} tLote;

void crearCola(tCola *cola);
int ponerEnCola(tCola *cola,const void* dato,unsigned tam);
int sacarDeCola(tCola *cola,void* dato,unsigned tam);
int verPrimero(const tCola *cola,void* dato,unsigned tam);
void vaciarCola(tCola *cola);
int colaVacia(const tCola *cola);
int colaLlena(const tCola *cola, unsigned tam);
int cargarArchivoPrueba(char *nombArchivo);
int bajarArchivo(char *archivo, tCola *cola);


#endif // HEAD_H_INCLUDED
