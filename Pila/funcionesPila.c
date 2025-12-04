#include "headPila.h"
void crearPila(tPila *p)
{
    *p=NULL;
}
void vaciarPila(tPila *p)
{
    tNodo *elim=*p;
    while(*p)
    {
        p=&(*p)->sig;
        free(elim->dato);
        free(elim);
        elim=*p;
    }

}
int apilar(tPila *p, const void *dato, unsigned tam)
{
    tNodo *nue=malloc(sizeof(tNodo));
    if(!nue)
        return 1;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 1;
    }

    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*p;
    *p=nue;
    return 0;
}
int desapilar(tPila *p, void *dato, unsigned tam)
{
    if(!*p)
        return 1;
    tNodo *elim=*p;
    memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
    *p=elim->sig;
    free(elim->dato);
    free(elim);
    return 0;
}
int verTope(const tPila *p, void *dato, unsigned tam)
{
    if(!*p)
        return 1;
    memcpy(dato,(*p)->dato,MINIMO(tam,(*p)->tam));
    return 0;
}
int pilaLlena(const tPila *p, unsigned tam)
{
    return 0;
}
int pilaVacia(const tPila *p)
{
    if(!*p)
        return 0;
    return 1;
}
