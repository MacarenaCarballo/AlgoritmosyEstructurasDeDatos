#include "pila_hibrida.h"


void crearPila(t_Pila* pila)
{
    pila->tope = TAM_PILA;
}


int apilar(t_Pila *pila,const void *dato, unsigned tam)
{
    if(pila->tope == 0)
        return PILA_LLENA;

    t_Info * nueInfo = (t_Info*)malloc(sizeof(t_Info));

    if(!nueInfo)
        return SIN_MEM;

    nueInfo->dato = malloc(tam);

    if(!nueInfo->dato)
    {
        free(nueInfo);
        return SIN_MEM;
    }

    memcpy(nueInfo->dato, dato, tam);
    nueInfo->tam = tam;

    pila->elementos[pila->tope -1] = nueInfo;
    pila->tope--;

    return TODO_OK;
}

int desapilar(t_Pila *pila, void * dato, unsigned tam)
{
    if(pila->tope == TAM_PILA)
        return PILA_VACIA;

    t_Info *elimInfo = pila->elementos[pila->tope];
    memcpy(dato,elimInfo->dato, MIN(tam,elimInfo->tam));

    free(elimInfo->dato);
    free(elimInfo);

    pila->tope++;

    return TODO_OK;
}


int verTope(const t_Pila *pila, void *dato, unsigned tam)
{
        if(pila->tope == TAM_PILA)
        return PILA_VACIA;

    t_Info *tope = pila->elementos[pila->tope];
    memcpy(dato,tope->dato, MIN(tam,tope->tam));

    return TODO_OK;
}

void vaciarPila(t_Pila *pila)
{
    while (pila->tope < TAM_PILA) {
        free(pila->elementos[pila->tope]->dato);
        free(pila->elementos[pila->tope]);
        pila->tope++;
    }
}


int pilaLlena(const t_Pila *pila)
{
    return pila->tope == 0;
}

int pilaVacia(const t_Pila *pila)
{
    return  pila->tope == TAM_PILA;
}
