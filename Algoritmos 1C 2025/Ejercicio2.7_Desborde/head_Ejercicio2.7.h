#ifndef HEAD_EJERCICIO2_7_H_INCLUDED
#define HEAD_EJERCICIO2_7_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 1000
#define PILA_LLENA 1
#define PILA_VACIA 2
#define PILA_NO_VACIA 0
#define PILA_DISPONIBLE 0
#define SATISFACTORIO 0
#define MINIMO(x, y) ((x) <= (y) ? (x) : (y))
#define ESDIGITO(x) ((x) >= '0' && (x) <= '9')
#define TAM_CAD 10000

typedef struct {
char pila[TAM];
int tope;}tPila;

void crearPila(tPila* pila);
//dato que no modifico y generico por es CONST VOID
//Paso el tipo de dato por copia ya que me ahorro  bytes
int apilar(tPila *pila,const void *dato, unsigned tam);
int desapilar(tPila *pila, void * dato, unsigned tam);
void vaciarPila(tPila *pila);
int verTope(const tPila *pila, void *dato, unsigned tam);
int pilaLlena(const tPila *pila, unsigned tam);
int pilaVacia(const tPila *pila);
int mi_Strlen(const char *dato);
int charAentero(char cad);
int bajarArchivoTxt(char * nombreArchivo, char *linea);
int sumaDosNumerosGrande(tPila* pila1, tPila *pila2, tPila* pilaRes);
int prepararPila(tPila *pila, char *linea);
int subirArchivoTxt(char * nombreArchivo,tPila *pila);

#endif // HEAD_EJERCICIO2_7_H_INCLUDED
