#include "headers.h"
void crear_tabla_puntos(t_tabla_puntos* p, unsigned tam)
{
    p->tam=tam;
    crearLista(&p->tabla);
}
int agregar_puntaje(t_tabla_puntos* p, const t_puntaje* dato)
{

}
void imprimir_tabla_puntos(t_tabla_puntos* p);
void vaciar_tabla_puntos(t_tabla_puntos* p);

void crearLista(t_lista *pl)
{
    *pl=NULL;
}
int insertarNodo(t_lista *pl,const void *dato, unsigned tam, tCmp comparar, unsigned top)
{
    //PRIMERO BUSCO LA POSICION SIN PASARME DEL LIMITE y mientras alla lista
    unsigned cont=0;
    while(*pl && comparar((*pl)->dato,dato)>0 && cont<top)
    {
        cont++;
        pl=&(*pl)->sig;
    }
    if(cont>=top)//El dato es mayor no entra
        return 1;

    tNodo *nue=malloc(sizeof(tNodo));
    if(!nue)
        return ERROR;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return ERROR;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pl;
    *pl=nue;

    // Ahora eliminar el último si hay más de topN elementos
    cont = 0;
    t_lista *pAux = pl;
    while(*pAux && cont < topN - 1)
    {
        cont++;
        pAux = &(*pAux)->sig;
    }

    // Si existe un nodo después de la posición topN-1, eliminarlo
    if(*pAux && (*pAux)->sig)
    {
        tNodo *aEliminar = (*pAux)->sig;
        (*pAux)->sig = NULL;
        free(aEliminar->dato);
        free(aEliminar);
    }

    return OK;
}

void vaciarLista(t_lista *pl)
{
    tNodo *elim;
    elim=*pl;
    while(*pl)
    {
        pl=&(*pl)->sig;
        free(elim->dato);
        free(elim);
        elim=*pl;
    }
    *pl=NULL;
}
int listaLlena(t_lista *pl, unsigned tam)
{
    return OK;
}
int listaVacia(t_lista *pl)
{
    if(*pl==NULL)
        return OK;
    return ERROR;
}
int compararEnteros(void *a, void *b)
{
    t_puntaje a1=*(t_puntaje*)a;
    t_puntaje b1=*(t_puntaje*)b;
    return a1.puntaje-b1.puntaje;
}
