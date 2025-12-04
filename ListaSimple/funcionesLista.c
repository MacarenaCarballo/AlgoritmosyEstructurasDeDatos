#include "headLista.h"

void crearLista(tLista *pl)
{
    *pl=NULL;
}

int insertarOrdenado(tLista *pl, const void *dato, unsigned tam, tCmp comparar)
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
    while(*pl && comparar((*pl)->dato,dato)<0)
        pl=&(*pl)->sig;

    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pl;
    *pl=nue;
    return 0;

}

int sacarLista(tLista *pl, void *dato, unsigned tam, tCmp comparar)
{
    if(!*pl)
        return 1;

    tNodo *elim;
    int comp;
    while(*pl && (comp=comparar((*pl)->dato,dato))!=0)
        pl=&(*pl)->sig;

    if(comp==0 && *pl)
    {
        elim=*pl;
        *pl=elim->sig;
        free(elim->dato);
        free(elim);
        return 0;
    }
    else
        return 1;

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
    tNodo *elim;
    while(*pl)
    {
        elim=*pl;
        *pl=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pl=NULL;
}

int compararCaracteres(const void *a, const void *b)
{
    char a1=*(char*)a;
    char b1=*(char*)b;
    return a1-b1;
}

void mapeo(tLista *pl, tAccion accion)
{
    if(!*pl)
        return;
    while(*pl)
    {
        accion((*pl)->dato,NULL);
        pl=&(*pl)->sig;
    }
}
void mostrarLista(void *a, void *b)
{
    char a1=*(char*)a;
    printf("%c\n",a1);
}
