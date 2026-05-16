#include "head.h"
void crearArbol(tArbol *p)
{
    *p=NULL;
}

int insertarArbolI(tArbol* p, void* dato, unsigned tam,tCmp cmp,tAccion accion)
{
    tNodo* nue;
    int resCmp;
    tNodo *act=*p;
    while(act)
    {
        if((resCmp=cmp(dato,act->dato))<0)
            act=act->izq;
        if(resCmp>0)
            act=act->der;
        if(resCmp==0)
        {
            if(accion)
                accion(act->dato,dato);
            return DUPLICADO;
        }
    }

    nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return SIN_MEM;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }

    memcpy(nue->dato,dato,tam);
    nue->tam= tam;
    nue->der= NULL;
    nue->izq= NULL;
    *p=nue;

    return SATISFACTORIO;
}

int insertarArbolR(tArbol* pa, void* dato, unsigned tam,tCmp cmp,tAccion accion)
{
    tNodo* nue;

    if(!*pa)//ESTE ES EL CASO BASE
    {
        nue=(tNodo*)malloc(sizeof(tNodo));
        if(!nue)
            return SIN_MEM;
        nue->dato=malloc(tam);
        if(!nue->dato)
        {
            free(nue);
            return SIN_MEM;
        }

        memcpy(nue->dato,dato,tam);
        nue->tam= tam;
        nue->der= NULL;
        nue->izq= NULL;

        *pa=nue;

        return SATISFACTORIO;
    }
    if(cmp(dato,(*pa)->dato)<0)
        return insertarArbolR(&(*pa)->izq,dato,tam,cmp,accion); //pa=&(*pa)->izq;
    if(cmp(dato,(*pa)->dato)>0)
        return insertarArbolR(&(*pa)->der,dato,tam,cmp,accion);//pa=&(*pa)->der;
    else
    {
        if(accion)
            accion((*pa)->dato,dato);
        return DUPLICADO;
    }
}
void recorrerPreorden(tArbol* pa, tAccion accion, void* param)
{
    if(!*pa)
        return;
    accion((*pa)->dato, param);
    recorrerPreorden(&(*pa)->izq,accion,param);
    recorrerPreorden(&(*pa)->der,accion,param);
}
void recorrerInorden(tArbol* pa, tAccion accion,void* param)
{
    if(!*pa)
        return;

    recorrerInorden(&(*pa)->izq,accion,param);
    accion((*pa)->dato, param);
    recorrerInorden(&(*pa)->der,accion,param);
}
void recorrerPostorden(tArbol* pa, tAccion accion, void* param)
{
    if(!*pa)
        return;

    recorrerPostorden(&(*pa)->izq,accion,param);//HIJO IZQ
    recorrerPostorden(&(*pa)->der,accion,param);//HIJO DERECHO
    accion((*pa)->dato, param);//RAIZ
}

int compararEnteros(void *a, void *b)
{
    return *(int*)a-*(int*)b;
}

void imprimirEnteros(void *dato, void *param)
{
    printf("%d\n",*(int*)dato);
}

void vaciarArbol(tArbol* pa)
{
    if (!*pa)
        return;

    vaciarArbol(&(*pa)->izq);
    vaciarArbol(&(*pa)->der);

    free((*pa)->dato);
    free(*pa);
    *pa = NULL;
}

int contarNodos(const tArbol* pa)
{
    int izq=0, der=0;

    if (!*pa)
        return 0;

    izq = contarNodos(&(*pa)->izq);
    der = contarNodos(&(*pa)->der);

    return 1 + izq + der;
}

int contarHojas(const tArbol* pa)
{
    if (!*pa)
        return 0;

    if (!(*pa)->izq && !(*pa)->der)
        return 1;

    return contarHojas(&(*pa)->izq) + contarHojas(&(*pa)->der);
}

int contarNohoja(const tArbol* pa)
{
    if (!*pa)
        return 0;

    if ((*pa)->izq != NULL || (*pa)->der != NULL)
        return 1+contarNohoja(&(*pa)->izq) + contarNohoja(&(*pa)->der);
    return 0;
}

int contarNodosConIzq(const tArbol* pa)
{
    if (!*pa)
        return 0;

    if((*pa)->izq)
        return 1+contarNodosConIzq(&(*pa)->izq)+contarNodosConIzq(&(*pa)->der);

    return 0;//SI NO ES NULO Y NO TIENE HIJO IZQ
}

unsigned alturaArbol(const tArbol *pa)
{
    int izq=0, der=0;
    if (*pa == NULL)
        return 0;

    izq = alturaArbol(&(*pa)->izq);
    der = alturaArbol(&(*pa)->der);

    return 1 + (izq > der ? izq : der);
}

unsigned cantNodosNivel(const tArbol *pa, unsigned nivel)
{
    if(!*pa)
        return 0;

    if(nivel==0)
        return 1;
    nivel--;
    return cantNodosNivel(&(*pa)->izq,nivel)+cantNodosNivel(&(*pa)->der,nivel);
}

unsigned cantNodosHastaNivel(const tArbol *pa, unsigned nivel)
{
    if(!*pa)
        return 0;

    if(nivel==0)
        return 1;
    nivel--;
    return 1+cantNodosHastaNivel(&(*pa)->izq,nivel)+cantNodosHastaNivel(&(*pa)->der,nivel);
}

unsigned cantNodosDesdeNivel(const tArbol *pa, unsigned nivel)
{
    if(!*pa)
        return 0;
    if(nivel==0)
        return 1+cantNodosDesdeNivel(&(*pa)->izq,nivel)+cantNodosDesdeNivel(&(*pa)->der,nivel);;
    nivel--;
    return cantNodosDesdeNivel(&(*pa)->izq,nivel)+cantNodosDesdeNivel(&(*pa)->der,nivel);

}

unsigned buscarClave(const tArbol *pa, tCmp comparar,void *clave)
{
    int cmp;

    if(!*pa)
        return 0;

    if((cmp=comparar(clave,(*pa)->dato))==0)
        return 1;
    else if(cmp<0)
        return buscarClave(&(*pa)->izq,comparar,clave);
    else
        return buscarClave(&(*pa)->der,comparar,clave);
}

unsigned cantNodosPorClaveDer(const tArbol *pa, tCmp comparar,void *clave)
{
    int cmp;

    if(!*pa)
        return 0;

    if((cmp=comparar(clave,(*pa)->dato))==0)
        return contarNodos(&(*pa)->der);

    else if(cmp<0)
        return cantNodosPorClaveDer(&(*pa)->izq,comparar,clave);
    else
        return cantNodosPorClaveDer(&(*pa)->der,comparar,clave);
}

int eliminarHoja(tArbol *pa, tCmp comparar,void *clave)
{
    int cmp;

    if(!*pa)
        return 0;

    if((cmp=comparar(clave,(*pa)->dato))==0)
    {
        if((*pa)->der==NULL && (*pa)->izq==NULL)
        {
            free((*pa)->dato);
            free(*pa);
            *pa=NULL;
            return 1;
        }
        else
            return 0;
    }
    else if(cmp<0)
        return eliminarHoja(&(*pa)->izq,comparar,clave);
    else
        return eliminarHoja(&(*pa)->der,comparar,clave);
}

int eliminarTodasHoja(tArbol *pa)
{
    if(!*pa)
        return 0;

    if((*pa)->der==NULL && (*pa)->izq==NULL)
    {
        free((*pa)->dato);
        free(*pa);
        *pa=NULL;
        return 1;
    }
    return eliminarTodasHoja(&(*pa)->izq)+eliminarTodasHoja(&(*pa)->der);
}

int eliminarDelArbol(tArbol *pa, void *dato, unsigned tam, tCmp comparar)
{
    if(!*pa)
        return 0;

    tArbol* elim = buscarClave2(pa, comparar, dato);
    if(!elim)
        return 0;

    // Caso 1: Nodo hoja (sin hijos)
    if((*elim)->der == NULL && (*elim)->izq == NULL)
    {
        free((*elim)->dato);
        free(*elim);
        *elim = NULL;
        return SATISFACTORIO;
    }

    // Caso 2 y 3: Nodo con uno o dos hijos
    tArbol* paR;
    tArbol nodoAEliminar; // Guardamos referencia al nodo que vamos a eliminar

    int altI = alturaArbol(&(*elim)->izq);
    int altD = alturaArbol(&(*elim)->der);

    if(altD > altI)
    {
        // Buscar el menor del subárbol derecho (sucesor inorden)
        paR = &(*elim)->der;
        while((*paR)->izq)
            paR = &(*paR)->izq;
    }
    else
    {
        // Buscar el mayor del subárbol izquierdo (predecesor inorden)
        paR = &(*elim)->izq;
        while((*paR)->der)
            paR = &(*paR)->der;
    }

    // Guardar referencia del nodo que vamos a eliminar físicamente
    nodoAEliminar = *paR;

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

    return SATISFACTORIO;
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

tArbol* buscarClave2(tArbol*pa,tCmp comparar,void *clave)
{
    if(!*pa)
        return NULL;

    int cmp;
    if((cmp=comparar(clave,(*pa)->dato))<0)
        return buscarClave2(&(*pa)->izq, comparar,clave);
    else if(cmp>0)
        return buscarClave2(&(*pa)->der, comparar,clave);
    else
        return pa;
}
