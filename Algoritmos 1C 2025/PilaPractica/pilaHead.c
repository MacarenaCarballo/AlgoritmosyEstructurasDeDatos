#include "pilaHead.h"
void crearPila(tPila *pp)
{
    *pp=NULL;
}
void vaciarPila(tPila *pp)
{
    tNodo *elim;
    while((*pp)->sig)
    {
        elim=*pp;
        *pp=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pp=NULL;
}

int insertarPila(tPila *pp, void *dato, unsigned tam)
{
    tNodo *nue=malloc(sizeof(tNodo));
    if(!nue)
        return 1;

    return 0;
}
