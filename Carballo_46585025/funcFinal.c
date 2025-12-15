#include "headFinal.h"
void crearArbol(tArbol *pa)
{
    *pa=NULL;
}
int insertarEnOrden(tArbol *pa, const void *dato, unsigned tam, tCmp comparar)
{
    if(!*pa)
    {
        tNodo *nue=malloc(sizeof(tNodo));
        if(!nue)
            return ERROR;
        nue->dato=malloc(tam);
        if(!nue->dato)
        {
            free(nue);
            return ERROR;
        }
        memcpy(nue->dato,dato, tam);
        nue->tam=tam;
        nue->der=NULL;
        nue->izq=NULL;
        *pa=nue;
        return HECHO;
    }
    if(comparar(dato,(*pa)->dato)<0)
        return insertarEnOrden(&(*pa)->izq,dato,tam,comparar);
    else if(comparar(dato,(*pa)->dato)>0)
        return insertarEnOrden(&(*pa)->der,dato,tam,comparar);
    else
        return HECHO; //NO ADMITE DUPLICADOS
}
void vaciarArbol(tArbol *pa)
{
    if(!*pa)
        return;
    vaciarArbol(&(*pa)->der);
    vaciarArbol(&(*pa)->izq);
    free((*pa)->dato);
    free(*pa);
    *pa=NULL;
}

int compararEnteros(const void *a, const void *b)
{
    int num1=*(int*)a;
    int num2=*(int*)b;
    return num1-num2;
}

void recorrerPreOrden(const tArbol *pa, tAccion mostrar, void *param)
{
    if(!*pa)
        return;
    recorrerPreOrden(&(*pa)->izq,mostrar,param);
    mostrar((*pa)->dato,param);
    recorrerPreOrden(&(*pa)->der,mostrar,param);
}
void mostrarEntero(void *a, void *b)
{
    int num1=*(int*)a;
    printf("El numero es: %d\n",num1);
}

int menorBuscar(tArbol *pa,tAccion comparar)
{
    if((*pa)==NULL)
        return 0;
    if((*pa)->der==NULL && (*pa)->izq==NULL)
    {
        comparar((*pa)->dato,NULL);
    }
    return menorBuscar(&(*pa)->izq,comparar);
}

int buscarSegundoMenor(const tArbol *pa, tCmp comparar)
{
    tNodo *menor, *segundoMenor;
    menor=*pa;
    segundoMenor=*pa;
    while(*pa)
    {
        if(comparar((*pa)->dato,menor->dato)<0)
        {
            segundoMenor=menor;
            menor=*pa;

        }
        else
            segundoMenor=*pa;
        if(!(*pa)->izq)
            pa=&(*pa)->der;
        else
            pa=&(*pa)->izq;
    }
    if(menor==segundoMenor)
    {
        printf("No hay segundo menor\n");
        return HECHO;
    }
    mostrarEntero(segundoMenor->dato,NULL);
    return HECHO;
}

