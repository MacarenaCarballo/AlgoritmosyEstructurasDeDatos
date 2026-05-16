#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define REALIZADO 0
#define DUPLICADO -1
#define ERRORCOD 1
#define NOENCONTRADO 2

typedef int (*tCmp)(void *a, void *b);
typedef int (*tAccion)(void *a, void *b);

typedef struct{
int dni;
char patente[8];}tClave;
typedef struct
{
    int a,m,d;
} Fecha;

typedef struct
{
    char patente[8];
    int nroCuota;
    char titular[26];
    int dni;
    Fecha vto;
    float importe;
} Registro;

typedef struct sNodo
{
    void *dato;
    unsigned tam;
    struct sNodo*sig;
    struct sNodo*ant;
}tNodo;

typedef tNodo *tLista;
int crearLote(char *nombre);
int leerArchivo(char *nombre,tLista *pl);
int compararDni(void *a, void *b);
int compararDniyPatente(void *a, void *b);
void crearLista(tLista *pl);
int insertarNodo(tLista *pl, void *dato, unsigned tam, tCmp comparar);
void vaciarLista(tLista *pl);
int filter(tLista *pl, tCmp comparar, tAccion accion, void *dato, void *param);
float deudaTotal(tLista *pl);
int compararImporte(void *a, void *b);
int crearDeuda(void *a, void *b);
 int cargarArchivoDNI(tLista *pl, FILE *pf, float deudaTotal);
 int cargarArchivoDNIyPatente(tLista *pl, FILE *pf, float deudaTotal);
 int mostrarListaPrincipio(tLista *lista,tAccion accion);
 int mostrarReg(void *a, void *b);
 int compararDniEspecifico(void *a, void *b);
  int compararDniyPatenteEspecifico(void *a, void *b);
#endif // HEAD_H_INCLUDED
