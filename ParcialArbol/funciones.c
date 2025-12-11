#include "headArbol.h"
void crearArbol(tArbol *pa)
{
    *pa=NULL;
}
int insertarR(tArbol *pa,const void *dato, unsigned tam, tCmp comparar)
{
    if(!*pa)
    {
        tNodo *nue=malloc(sizeof(tNodo));
        if(!nue)
            return 1;
        nue->dato=malloc(tam);
        if(!nue->dato)
        {
            free(nue->dato);
            return 1;
        }
        memcpy(nue->dato,dato,tam);
        nue->tam=tam;
        nue->der=NULL;
        nue->izq=NULL;
        *pa=nue;
        return 0;
    }

    if(comparar((*pa)->dato,dato)<0)
        return insertarR(&(*pa)->der,dato,tam, comparar);
    else if(comparar((*pa)->dato,dato)>0)
        return insertarR(&(*pa)->der,dato,tam, comparar);
    else
        return 0;
}
void vaciarArbol(tArbol *pa)
{
    if(!*pa)
        return;
    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);
    free((*pa)->dato);
    free(*pa);
    *pa=NULL;
}

int bajarArchivo(char *archivo, tArbol *pa)
{
    FILE *pf=fopen(archivo,"rt");
    if(!pf)
        return 1;
    char linea[20];
    int clave, noclave;
    tDato reg;
    while(fgets(linea,20,pf))
    {
        sscanf(linea,"%d,%d",&clave,&noclave);
        reg.clave=clave;
        reg.noClave=noclave;
        insertarR(pa,&reg,sizeof(tDato),compararClave);
    }
    fclose(pf);
    return 0;
}


void recorrerInOrden(tArbol *pa, tAccion accion)
{
    if(!*pa)
        return;
    recorrerInOrden(&(*pa)->izq, accion);
    accion((*pa)->dato,NULL);
    recorrerInOrden(&(*pa)->der, accion);
}
void mostrar( void *a, const void *b)
{
    tDato p1=*(tDato*)a;
    printf("Clave:%d| Dato:%d\n",p1.clave,p1.noClave);
}
int contarocurrencias(tArbol *pa,const void *dato, tCmp comparar)
{
    if(!*pa)
        return 0;
    if(comparar((*pa)->dato,dato)==0)
        return 1+contarocurrencias(&(*pa)->izq,dato,comparar)+contarocurrencias(&(*pa)->der,dato,comparar);
    return contarocurrencias(&(*pa)->izq,dato,comparar)+contarocurrencias(&(*pa)->der,dato,comparar);
}
int compararNoclave(const void *a,const void *b)
{
    tDato p1=*(tDato*)a;
    int p2=*(int*)b;
    return p1.noClave-p2;
}
int compararClave(const void *a,const void *b)
{
    tDato p1=*(tDato*)a;
    tDato p2=*(tDato*)b;
    return p1.clave-p2.clave;
}

void espejarArbol(tArbol *pa)
{
    if(!*pa)
        return;
    tNodo *aux;
    aux=(*pa)->der;
    (*pa)->der=(*pa)->izq;
    (*pa)->izq=aux;
    espejarArbol(&(*pa)->izq);
    espejarArbol(&(*pa)->der);
}
