#include "headCola.h"
void crearCola(tCola *cola)
{
    cola->pri=NULL;
    cola->ult=NULL;
}
int ponerEnCola(tCola *cola,const void* dato,unsigned tam)
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
    nue->sig=NULL;

    if(!cola->pri)
        cola->pri=nue;
    else
        cola->ult->sig=nue;

    cola->ult=nue;
    return 0;

}
int sacarDeCola(tCola *cola,void* dato,unsigned tam)
{
    if(!cola->pri)
        return 1;

    tNodo *elim;
    elim=cola->pri;
    cola->pri=elim->sig;
    memcpy(dato,elim->dato,MINIMO(elim->tam,tam));
    free(elim->dato);
    free(elim);
    if(!cola->pri)
        cola->ult=NULL;
    return 0;

}

int verPrimero(const tCola *cola,void* dato,unsigned tam)
{
    if(!cola->pri)
        return 1;
    memcpy(dato,cola->pri->dato,MINIMO(cola->pri->tam,tam));
    return 0;
}

void vaciarCola(tCola *cola)
{
    tNodo *elim;
    while(cola->pri)
    {
        elim=cola->pri;
        cola->pri=elim->sig;
        free(elim->dato);
        free(elim);
    }
    cola->pri=NULL;
    cola->ult=NULL;
}

int colaVacia(const tCola *cola)
{
    if(cola->pri==NULL)
        return 0;
    return 1;
}
int colaLlena(const tCola *cola, unsigned tam)
{
    return 0;
}
