#include "headListaCir.h"
void crearLista(tLista *pl)
{
    *pl=NULL;
}
int listaLlena(const tLista *pl, unsigned tam)
{
    return 0;
}
int listaVacia(const tLista *pl)
{
    if(*pl==NULL)
        return 0;
    return 1;
}
void vaciarLista(tLista *pl)
{
    tNodo *elim=(*pl)->sig;
    while(*pl!=elim)
    {
        *pl=elim->sig;
        free(elim->dato);
        free(elim);
        elim=*pl;
    }
    free(elim->dato);
    free(elim);
    *pl=NULL;
}

int compararCaracteres(const void *a, const void *b)
{
    char a1=*(char*)a;
    char b1=*(char*)b;
    return a1-b1;
}
void mostrarLista(void *a, void *b)
{
    char a1=*(char*)a;
    printf("%c\n",a1);
}

int insertarOrdenado(tLista *pl,const void *dato,unsigned tam)
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
    if(!*pl)
        nue->sig=nue;
    else
    {
        nue->sig=(*pl)->sig;
        (*pl)->sig=nue;
    }

    *pl=nue;
    return 0;

}

void mapeo(tLista *pl, tAccion accion)
{
    if(!*pl)
        return;
    tNodo *pri=*pl;
    while((*pl)->sig!=pri)
    {
        accion((*pl)->dato,NULL);
        pl=&(*pl)->sig;
    }
    accion((*pl)->dato,NULL);
}
int sacarUltimo(tLista *pl, void *dato, unsigned tam)
{
    if(!*pl)
        return 1;
    tNodo *elim=(*pl)->sig;
    (*pl)->sig=elim->sig;
    memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
    free(elim->dato);
    free(elim);
    return 0;

}
