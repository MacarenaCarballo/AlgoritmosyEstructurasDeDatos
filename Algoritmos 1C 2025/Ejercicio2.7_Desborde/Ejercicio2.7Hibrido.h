#ifndef EJERCICIO2_7HIBRIDO_H_INCLUDED
#define EJERCICIO2_7HIBRIDO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TAM_PILA 10000
#define TODO_OK       0
#define SIN_MEM      -3
#define MIN(a,b) (a) < (b)? (a) : (b)

typedef struct {
    void *dato;
    size_t tam;
} t_Info;


typedef struct {
    t_Info *elementos[TAM_PILA];
    int tope;
} t_Pila;

void crearPilaH(t_Pila* pila);
int apilarH(t_Pila *pila,const void *dato, unsigned tam);
int desapilarH(t_Pila *pila, void * dato, unsigned tam);
void vaciarPilaH(t_Pila *pila);
int verTopeH(const t_Pila *pila, void *dato, unsigned tam);
int pilaLlenaH(const t_Pila *pila);
int pilaVaciaH(const t_Pila *pila);
int sumaDosNumerosGrandeH(t_Pila* pila1, t_Pila *pila2, t_Pila* pilaRes);
int prepararPilaH(t_Pila *pila, char *linea);
int subirArchivoTxtH(char * nombreArchivo,t_Pila *pila);

#endif // EJERCICIO2_7HIBRIDO_H_INCLUDED
