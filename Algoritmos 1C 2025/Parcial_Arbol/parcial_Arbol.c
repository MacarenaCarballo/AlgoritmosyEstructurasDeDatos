#include "parcialArbol.h"
void crearArbol(tArbol *pa)
{
    *pa=NULL;
}

int procesarArchivos(char *nombreArch, tArbol *pa, tCmp comparar)
{
    char palabraBuffer[MAXLINEA+1];
    char palabra[MAXLINEA+1];
    FILE *pf = fopen(nombreArch, "rt");
    char *palabraGuardar;
    char *letra;
    int palabraEnProceso = 0;

    if(!pf)
        return ERRORCOD;

    palabraGuardar = palabra;

    while(fgets(palabraBuffer, MAXLINEA+1, pf))
    {
       // printf("%s\n", palabraBuffer);
        letra = palabraBuffer;

        while(*letra != '\0')
        {
            if(ES_CARACTER(*letra))
            {
                *palabraGuardar = *letra;
                palabraGuardar++;
                palabraEnProceso = 1;
            }
            else
            {
                if(palabraEnProceso && *letra!='\n')
                {
                    *palabraGuardar = '\0';
                    printf("%s\n", palabra);
                    insertarEnArbol(pa,&palabra,strlen(palabra)+1,comparar);
                    palabraGuardar = palabra;
                    palabraEnProceso = 0;
                }
            }
            letra++;
        }
    }

    if(palabraEnProceso)
    {
        *palabraGuardar = '\0';
        printf("%s\n", palabra);
        insertarEnArbol(pa,&palabra,strlen(palabra)+1,comparar);
    }

    fclose(pf);
    return REALIZADO;
}

int insertarEnArbol(tArbol *pa,void *dato, unsigned tam, tCmp comparar)
{
    if(!*pa)
    {
        tNodo *nue;
        nue=malloc(sizeof(tNodo));
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
        nue->izq=NULL;
        nue->der=NULL;
        *pa=nue;
        return REALIZADO;
    }
    int cmp;

    if((cmp=comparar(dato,(*pa)->dato))<0)
        return insertarEnArbol(&(*pa)->izq,dato, tam, comparar);
    else if(cmp>0)
        return insertarEnArbol(&(*pa)->der,dato, tam, comparar);
    else
        return DUPLICADO;
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
int eliminarDelArbol(tArbol *pa, void *dato, unsigned tam, tCmp comparar)
{
    if(!*pa)
        return 0;

    tArbol* elim = buscarClave(pa, comparar, dato);
    if(!elim)
        return 0;

    if((*elim)->der == NULL && (*elim)->izq == NULL)
    {
        free((*elim)->dato);
        free(*elim);
        *elim = NULL;
        return REALIZADO;
    }

    tArbol* paR;
    tArbol nodoAEliminar;

    int altI = alturaArbol(&(*elim)->izq);
    int altD = alturaArbol(&(*elim)->der);

    if(altD > altI)
    {
        paR = &(*elim)->der;
        while((*paR)->izq)
            paR = &(*paR)->izq;
    }
    else
    {
        paR = &(*elim)->izq;
        while((*paR)->der)
            paR = &(*paR)->der;
    }

    nodoAEliminar = *paR;

    intercambio(elim, paR);

    if((*paR)->der)
        *paR = (*paR)->der;
    else if((*paR)->izq)
        *paR = (*paR)->izq;
    else
        *paR = NULL;

    free(nodoAEliminar->dato);
    free(nodoAEliminar);

    return REALIZADO;
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

unsigned alturaArbol(const tArbol *pa)
{
    int izq=0,der=0;
    if(!*pa)
        return 0;
    izq=alturaArbol(&(*pa)->izq);
    der=alturaArbol(&(*pa)->der);
    return 1+(izq>der?izq:der);
}

tArbol* buscarClave(tArbol*pa,tCmp comparar,void *clave)
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

int compararStrings(void *a, void *b)
{
    return stricmp((char*)a,(char*)b);
}

void recorrerInOrden(tArbol *pa, tAccion accion, void *parm)
{
    if(!*pa)
        return;
    recorrerInOrden(&(*pa)->izq,accion,parm);
    accion((*pa)->dato,parm);
    recorrerInOrden(&(*pa)->der,accion,parm);
}

void mostrarString(void *a, void *b)
{
    printf("[%s]\n",(char*)a);
}

void archivoString(void *a, void *b)
{
    if(!a || !b)
        return;
    fprintf((FILE*)b,"%s\n",(char*)a);
}

int aMENOSb(tArbol *pa, tArbol *pb)
{
    if(!*pb)
        return 0;

    if(!*pa)
        return 0;

    eliminarDelArbol(pa, (*pb)->dato, (*pb)->tam, compararStrings);

    aMENOSb(pa, &(*pb)->izq);
    aMENOSb(pa, &(*pb)->der);

    return REALIZADO;
}
