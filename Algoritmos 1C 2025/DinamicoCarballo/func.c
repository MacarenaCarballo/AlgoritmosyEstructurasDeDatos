#include "func.h"

void crearPila(tPila* pila)
{
    *pila=NULL;
}

int pilaVacia(const tPila *pila)
{
    if (*pila==NULL)
        return PILA_VACIA;
    return PILA_NO_VACIA;
}

int apilar(tPila *pila, void *dato, unsigned tam)
{
    tNodo *nuevo=(tNodo*)malloc(sizeof(tNodo));
    if(!nuevo)
        return SIN_MEM;

    nuevo->dato=malloc(tam);
    if(!nuevo->dato)
    {
        free(nuevo);
        return SIN_MEM;
    }

    memcpy(nuevo->dato,dato,tam);
    nuevo->tam=tam;
    nuevo->sig=*pila;

    *pila=nuevo;
    return REALIZADO;
}

int pilaLlena(const tPila *pila, unsigned tam)
{
    return PILA_DISPO;
}

int desapilar(tPila *pila, void* dato, unsigned tam)
{
    tNodo *elim;
    elim=*pila;

    if (elim==NULL)
        return PILA_VACIA;

    memcpy(dato,elim->dato,MINIMO(elim->tam,tam));

    *pila=elim->sig;

    free(elim->dato);
    free(elim);

    return REALIZADO;
}

int verTope(tPila *pila, void *dato, unsigned tam)
{
    if(*pila==NULL)
        return PILA_VACIA;

    memcpy(dato,(*pila)->dato,MINIMO((*pila)->tam,tam));
    return REALIZADO;
}

void vaciarPila(tPila *pila)
{
    tNodo *aux;
    while(*pila)
    {
        aux=*pila;
        *pila=aux->sig;
        free(aux->dato);
        free(aux);
    }
}
