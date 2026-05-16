#include "headRecuperatorio.h"
void crearArbol(tArbol *pa)
{
    *pa=NULL;
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

int crearLote(char *lote)
{
    FILE *pf=fopen(lote,"wt");
    if(!pf)
        return 1;
    tInfo vec[]= {{3, 50},
        {2, 50},
        {1, 50},
        {4, 70},
        {6, 30},
        {5, 9}
    };
    for(int i=0; i<6; i++)
    {
        fprintf(pf,"%d|%d\n",vec[i].clave,vec[i].dato);
    }
    fclose(pf);
    return 0;
}

int insertarEnArbol(tArbol *pa, void *dato, unsigned tam, tCmp comparar)
{
    tNodo *nue;
    if(*pa==NULL)
    {
        nue=malloc(sizeof(tNodo));
        if(!nue)
            return 1;
        nue->dato=malloc(tam);
        if(!nue->dato)
        {
            free(nue);
            return 1;
        }
        nue->tam=tam;
        nue->der=NULL;
        nue->izq=NULL;
        memcpy(nue->dato,dato,tam);
        *pa=nue;
        return 0;
    }
    if(comparar(dato,(*pa)->dato)>0)
        return insertarEnArbol(&(*pa)->der,dato,tam,comparar);
    else if(comparar(dato,(*pa)->dato)<0)
        return insertarEnArbol(&(*pa)->izq,dato,tam,comparar);
    else
        return 1;//duplicado
}

int compararClave(void *a, void *b)
{
    tInfo n1=*(tInfo*)a;
    tInfo n2=*(tInfo*)b;
    return n1.clave-n2.clave;
}
int compararDato(void *a, void *b)
{
    tInfo n1=*(tInfo*)a;
    int n2=*(int*)b;
    return n1.dato-n2;
}

void mostrarArbol(void *a, void *b)
{
    tInfo data=*(tInfo*)a;
    printf("CLAVE: %d| DATO: %d\n",data.clave,data.dato);
}

void recorrerInOrden(tArbol *pa, tAccion accion)
{
    if(!*pa)
        return;
    accion((*pa)->dato, NULL);
    recorrerInOrden(&(*pa)->izq,accion);
    recorrerInOrden(&(*pa)->der,accion);
}

int cargarArbol(tArbol *pa, char *nombre)
{
    char linea[20];
    tInfo reg;
    FILE *pf=fopen(nombre,"rt");
    if(!pf)
        return 1;
    while(fgets(linea,20,pf))
    {
        trozado(linea,&reg);
        insertarEnArbol(pa,&reg, sizeof(tInfo),compararClave);
    }
    fclose(pf);
    return 0;
}

void trozado(char *linea, tInfo *reg)
{
    char *act;
    act=strrchr(linea,'\n');
    *act='\0';
    act=strrchr(linea,'|');
    reg->dato=atoi(act+1);
    *act='\0';
    reg->clave=atoi(linea);
}

int contarOcurrencias(tArbol *pa, tCmp comparar, void *datoNoClave)
{
    if(!*pa)
        return 0;
    if(comparar((*pa)->dato,datoNoClave)==0)
        return 1+contarOcurrencias(&(*pa)->izq,comparar,datoNoClave)+contarOcurrencias(&(*pa)->der,comparar,datoNoClave);;
    return contarOcurrencias(&(*pa)->izq,comparar,datoNoClave)+contarOcurrencias(&(*pa)->der,comparar,datoNoClave);
}

void espejarArbol(tArbol *pa)
{
    tNodo *aux;
    if(!*pa)
        return;
    aux=(*pa)->izq;
    (*pa)->izq=(*pa)->der;
    (*pa)->der=aux;
    espejarArbol(&(*pa)->izq);
    espejarArbol(&(*pa)->der);
}
