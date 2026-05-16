#include "funciones.h"
void crearPila(tPila* pila)
{
    pila->tope=TAM;
}

int apilar(tPila *pila,const void *dato, unsigned tam)
{
    if(pila->tope < tam + sizeof(unsigned))
    {
        return PILA_LLENA;
    }
    pila->tope-=tam;
    memcpy( pila->pila+pila->tope,dato,tam);
    pila->tope-= sizeof(tam);
    memcpy(pila->pila+pila->tope,&tam,sizeof(tam));

    return SATISFACTORIO;

}

int pilaLlena(const tPila *pila, unsigned tam)
{
//    return pila->tope < (tam + sizeof(unsigned));
    if(pila->tope < tam + sizeof(unsigned))
    {
        return PILA_LLENA;
    }
    return PILA_DISPONIBLE;
}

int pilaVacia(const tPila *pila)
{
//    return pila->tope==TAM;
    if(pila->tope==TAM)
    {
        return PILA_VACIA;
    }
    return PILA_NO_VACIA;
}

int verTope(const tPila *pila, void *dato, unsigned tam)
{
    unsigned tamInfo;
    if(pila->tope==TAM)
    {
        return PILA_VACIA;
    }
    //guardo el tamaño de la info que le sigue ya que tengo que comparar
    memcpy(&tamInfo,pila->pila+pila->tope,sizeof(unsigned));
    //EN EL MEMCCPY NO SE MUEVE EL PUNTERO, POR LO TANTO QUEDA IGUAL
    //HAGO TODO DENTRO DEL MEMCPY PARA NO MODIFICARLO
    memcpy(dato,pila->pila+pila->tope+sizeof(unsigned), MINIMO(tam,tamInfo));
    return SATISFACTORIO;
}

void vaciarPila(tPila *pila)
{
    pila->tope=TAM;
}

int desapilar(tPila *pila, void * dato, unsigned tam)
{
    unsigned tamInfo;
    if(pila->tope==TAM)
    {
        return PILA_VACIA;
    }
    memcpy(&tamInfo,pila->pila+pila->tope,sizeof(unsigned));
    pila->tope+=sizeof(unsigned);
    memcpy(dato,pila->pila+pila->tope,MINIMO(tam,tamInfo));
    //TAMAÑO DEL DATO DE LA PILA, YA QUE ME TENGO QUE QUEDAR PARA EL PROXIMO DATO
    pila->tope+=tamInfo;
    return SATISFACTORIO;
}


int mi_Strlen(const char *dato)
{
    int cont=0;
    while(*dato!='\0')
    {
        cont++;
        dato++;
    }
    return cont;
}
