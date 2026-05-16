#include "lista_head.h"
void crearLista(tLista* lista)
{
    *lista=NULL;
}
int listaLlena(const tLista *lista,unsigned tam)
{
    return LISTA_DISPO;
}

int listaVacia(const tLista *lista)
{
    if(*lista==NULL)
        return LISTA_VACIA;
    return LISTA_NO_VACIA;
}

int agregarNodo(tLista *lista, const void *dato, unsigned tam)
{
    tNodo *nue=(tNodo*)malloc(sizeof(tNodo));

    if(!nue)
        return SIN_MEM;

    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }



    memcpy(nue->dato,dato,tam);
    nue->tam=tam;

    if(*lista==NULL)
    {
        nue->sig=nue;

    }
    else
    {
        nue->sig=(*lista)->sig;
        (*lista)->sig = nue;

    }
    *lista=nue;

    return REALIZADO;
}

//int agegarAPila(tLista *lista, const void *dato, unsigned tam)
//{
//    tNodo *nue=(tNodo*)malloc(sizeof(tNodo));
//
//    if(!nue)
//        return SIN_MEM;
//
//    nue->dato=malloc(tam);
//    if(!nue->dato)
//    {
//        free(nue);
//        return SIN_MEM;
//    }
//
//
//
//    memcpy(nue->dato,dato,tam);
//    nue->tam=tam;
//
//    if(*lista==NULL)
//    {
//        nue->sig=nue;
//        *lista=nue;
//    }
//
//    else
//    {
//        nue->sig=(*lista)->sig;
//        (*lista)->sig = nue;
//    }
//
//
//    return REALIZADO;
//}
//int agegarACola(tLista *lista, const void *dato, unsigned tam)
//{
//    tNodo *nue=(tNodo*)malloc(sizeof(tNodo));
//
//    if(!nue)
//        return SIN_MEM;
//
//    nue->dato=malloc(tam);
//    if(!nue->dato)
//    {
//        free(nue);
//        return SIN_MEM;
//    }
//
//
//
//    memcpy(nue->dato,dato,tam);
//    nue->tam=tam;
//
//    if(*lista==NULL)
//    {
//        nue->sig=nue;
//
//    }
//    else
//    {
//        nue->sig=(*lista)->sig;
//        (*lista)->sig = nue;
//
//    }
//    *lista=nue;
//
//    return REALIZADO;
//}

int eliminarNodo(tLista *lista, void *dato, unsigned tam)
{
    tNodo *elim;

    if(*lista==NULL)
        return LISTA_VACIA;

    elim=(*lista)->sig;
    (*lista)->sig=elim->sig;

    memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
    free(elim->dato);
    free(elim);

    return REALIZADO;
}


int mapLista(tLista *lista, Funcion accion)
{
    tNodo *pri;
    pri=*lista;

    while((*lista)->sig!=pri)
    {
        accion((*lista)->sig->dato,NULL);
        lista=&(*lista)->sig;
    }
    accion((*lista)->sig->dato,NULL);
    return REALIZADO;
}

void vaciarLista(tLista *lista)
{
    if (!lista || !*lista)
        return;

    tNodo *elim = (*lista)->sig;

    while (elim != *lista)
    {
        (*lista)->sig = elim->sig;
        free(elim->dato);
        free(elim);
        elim = (*lista)->sig;
    }

    free((*lista)->dato);
    free(*lista);
    *lista = NULL;
}

void mostrarEntero(void *dato, void *nada)
{
    printf("El numero es: %d\n",*(int*)dato);
    //CASTEO EL PUNTERO A VOID A UN PUNTERO A INT Y MUESTRO SU CONTENIDO!!!
}
