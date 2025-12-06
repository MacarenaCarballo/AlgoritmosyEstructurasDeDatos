#include "headArbol.h"
void mostrarLista(void *a, void *b)
{
    char a1=*(char*)a;
    printf("%c\n",a1);
}
int compararCaracteres(const void *a, const void *b)
{
    char a1=*(char*)a;
    char b1=*(char*)b;
    return a1-b1;
}
void crearArbol(tArbol *pa)
{
    *pa=NULL;
}
int insertarOrdenado(tArbol *pa, void *dato,unsigned tam, tCmp comparar)
{
    if(!*pa)
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
        nue->der=NULL;
        nue->izq=NULL;
        *pa=nue;
        return 0;
    }
    if(comparar(dato,(*pa)->dato)>0)
        return insertarOrdenado(&(*pa)->der,dato,tam,comparar);
    else if(comparar(dato,(*pa)->dato)<0)
        return insertarOrdenado(&(*pa)->izq,dato,tam,comparar);
    else
        return 1;
}
int eliminarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar);
int arbolVacio(const tArbol *pa)
{
    if(!*pa)
        return 0;
    return 1;
}
int arbolLleno(const tArbol *pa,unsigned tam)
{
    return 0;
}
void vaciarArbol(tArbol *pa)
{
    if(!*pa)
        return;
    //VOY HASTA ABAJO Y LIBERO
    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);
    free((*pa)->dato);
    free(*pa);
    *pa=NULL;
}
int contarNodos(const tArbol *pa)
{
    if(!*pa)
        return 0;
    return 1+ contarNodos(&(*pa)->izq)+contarNodos(&(*pa)->der);
}
int alturaArbol(const tArbol *pa)
{
    if(!*pa)
        return 0;
    int izq=0,der=0;
    izq=alturaArbol((&(*pa)->izq));
    der=alturaArbol((&(*pa)->der));
    return 1+MAXIMO(izq,der);
}

void recorrerPreorden(const tArbol *pa, tAccion accion)
{
    if(!*pa)
        return;
    accion((*pa)->dato,NULL);
    recorrerPreorden(&(*pa)->izq,accion);
    recorrerPreorden(&(*pa)->der,accion);
}

int eliminarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar)
{
    // 1 si no hay arbol me voy
    if(!*pa)
        return 1;

    // 2 busco el nodo
    tArbol *elim=buscarClave(pa,comparar,dato);
    if(!elim)
        return 1;

    // 3 si es hoja elimino
    if((*elim)->der==NULL && (*elim)->izq==NULL)
    {
        free((*elim)->dato);
        free(*elim);
        *elim=NULL;
        return 0;
    }

    // 4 sino calculo la altura y elijo la mayor
    tArbol *paR;
    tArbol nodoAEliminar;
    int izq,der;
    izq=alturaArbol(&(*elim)->izq);
    der=alturaArbol(&(*elim)->der);
    if(izq<der)
    {
        paR = &(*elim)->der; //voy para el mas grande
        while((*paR)->izq)
            paR = &(*paR)->izq; //busco el menor del arbol derecho
    }else
    {
        paR = &(*elim)->izq; //voy para el mas grande
        while((*paR)->der)
            paR = &(*paR)->der;
    }
    nodoAEliminar=*paR;
    // Intercambiar los datos (no los nodos)
    intercambio(elim, paR);

    // Ahora eliminar el nodo reemplazante (que está en paR)
    // Este nodo puede tener como máximo un hijo
    if((*paR)->der)
        *paR = (*paR)->der;
    else if((*paR)->izq)
        *paR = (*paR)->izq;
    else
        *paR = NULL;

    // Liberar el nodo que eliminamos físicamente
    free(nodoAEliminar->dato);
    free(nodoAEliminar);

    return 0;
}

void intercambio(tArbol *elim, tArbol *paR)
{
    void *auxDato = (*elim)->dato;
    unsigned auxTam = (*elim)->tam;

    (*elim)->dato = (*paR)->dato;
    (*elim)->tam = (*paR)->tam;

    (*paR)->dato = auxDato;
    (*paR)->tam = auxTam;
}


tArbol* buscarClave( tArbol *pa, tCmp comparar,void *clave)
{
    if(!*pa)
        return NULL;

    int cmp;
    if((cmp=comparar(clave,(*pa)->dato))<0)
        return buscarClave(&(*pa)->izq, comparar,clave);
    else if(cmp>0)
        return buscarClave(&(*pa)->der, comparar,clave);
    else
        return pa;
}
