#include "lista_head.h"
#include "pilaDinamica.h"
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

int ponerAlComienzo(tLista *lista, void *dato, unsigned tam)
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
    nue->sig=*lista;

    *lista=nue;
    return REALIZADO;

}
int ordenarLista(tLista *pLista,tComparar cmp)
{
    if(*pLista==NULL)
        return LISTA_VACIA;
    //SI ESTA VACIA NO ORDENA

    if((*pLista)->sig==NULL)
        return REALIZADO;
    //SI HAY UN SOLO ELEMENTO YA ESTA ORDENADO

    int ordenado;
    tNodo *fin = NULL;

    do {
        ordenado = 1;
        tNodo *act = *pLista;

        while (act->sig != fin) {
            if (cmp(act->dato, act->sig->dato) > 0) {
                intercambiarNodos(act, act->sig);
                ordenado = 0;
            }
            act = act->sig;
        }

        fin = act;
    } while (!ordenado);

    return REALIZADO;

}
int ordenamientoDeNodos(tLista *pLista,tComparar cmp)
{
    tLista *ant=pLista;
    tLista *menor;
    tNodo *auxIntercambio;
    while(*ant)
    {
        menor=buscarMenor(ant,cmp);
        if(menor!=ant)
        {
            auxIntercambio=*menor;//AUX LE PONGO EL MENOR
            *menor=auxIntercambio->sig;//EL NODO QUE APUNTABA AL MENOR LE PONGO EL SIGUIENTE DE MENOR
            auxIntercambio->sig=*ant;//AL SIG DE MENOR LE PONGO LO QUE VENIA EN LA LISTA
            *ant=auxIntercambio;//Y AHORA EL PLISTA APUNTA AL MENOR YA ORDENADO

        }
        ant=&(*ant)->sig;
    }
    return REALIZADO;
}

tLista*  buscarMenor(tLista *pLista,tComparar cmp)
{
    tLista *menor=pLista;
    tLista *act=&(*pLista)->sig;

    while(*act)
    {
        if(cmp((*menor)->dato,(*act)->dato)>0)
            menor=act;
        act=&(*act)->sig;//ME DEVUELVE EL PUNTERO AL SIGUIENTE QUE APUNTA AL MENOR
    }
    return menor;
}

void intercambiarNodos(tNodo *nodo1, tNodo *nodo2)
{
    void *auxDato;
    unsigned auxTam;
    auxDato=nodo1->dato;
    auxTam=nodo1->tam;

    nodo1->dato=nodo2->dato;
    nodo1->tam=nodo2->tam;

    nodo2->dato=auxDato;
    nodo2->tam=auxTam;

}

int insertarEnOrden(tLista *pLista,const void *dato, unsigned tam,tComparar cmp, int duplicado,Funcion accion)
{

    while(*pLista && cmp(dato,(*pLista)->dato)>0)
    {
        pLista= &(*pLista)->sig;
    }

    //CON 1 NO ACEPTO DUPLICADOS POR LO TANTO HAGO LA ACCION Y SALGO
    if(*pLista && duplicado==1 && cmp(dato,(*pLista)->dato)==0)
    {
        accion((*pLista)->dato,NULL);
        return DUPLICADO;
    }

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

    nue->sig=*pLista;
    *pLista=nue;

    return REALIZADO;


}

int compararEnteros(const void * info1,const void *info2)
{
    int num1=*(int*)info1;
    int num2=*(int*)info2;
    return num1-num2;
}

int compararLetras(const void * info1,const void *info2)
{
    char num1=*(char*)info1;
    char num2=*(char*)info2;
    return num2-num1;
}

int eliminarNodoSinDuplicadosOrdenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp)
{
    tNodo *elim;
    int comparacion;
    while(*pLista && (comparacion=(cmp(dato,(*pLista)->dato)))>0)
    {
        pLista= &(*pLista)->sig;
    }
    if(*pLista && comparacion==0)
    {
        elim=*pLista;
        memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
        *pLista=elim->sig;
        free(elim->dato);
        free(elim);

    }
    else
    {
        //NODO NO ENCONTRADO
        return 1;
    }
    return REALIZADO;

}

int eliminarNodoDuplicadosOrdenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp)
{
    tNodo *elim;
    int comparacion;
    while(*pLista && (comparacion=(cmp(dato,(*pLista)->dato)))>0)
    {
        pLista= &(*pLista)->sig;
    }
    if(!*pLista || comparacion!=0)
        return 1;
    tNodo *aux=*pLista;
    do
    {
        elim=*pLista;
        *pLista=elim->sig;
        memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
        free(elim->dato);
        free(elim);
    }
    while(cmp((*pLista)->dato,dato)==0);
    aux->sig=*pLista;
    return REALIZADO;

}

int eliminarNodoSinDuplicadosDesordenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp)
{
    tNodo *elim;
    int comparacion;
    while(*pLista && (comparacion=(cmp(dato,(*pLista)->dato)))!=0)
    {
        pLista= &(*pLista)->sig;
    }
    if(*pLista && comparacion==0)
    {
        elim=*pLista;
        memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
        *pLista=elim->sig;
        free(elim->dato);
        free(elim);

    }
    else
    {
        //NODO NO ENCONTRADO
        return 1;
    }
    return REALIZADO;
}
int eliminarNodoDuplicadosDesordenada(tLista *pLista, void *dato, unsigned tam,tComparar cmp)
{
    tNodo *elim;

    if(!*pLista)
        return 1;

    while(*pLista)
    {
        if(cmp(dato,(*pLista)->dato)==0)
        {
            elim=*pLista;
            *pLista=elim->sig;
            memcpy(dato,elim->dato,MINIMO(tam,elim->tam));
            free(elim->dato);
            free(elim);
        }
        else
            pLista= &(*pLista)->sig;
    }

    return REALIZADO;
}
int mostrarLista(tLista *lista, Mostrar mostrarDato)
{
    tLista *pLista;
    if(*lista==NULL)
    {
        printf("LA LISTA ESTA VACIA!\n");
        return LISTA_VACIA;
    }
    pLista=lista;
    while(*pLista!=NULL)
    {
        mostrarDato((*pLista)->dato); //mostrar
        pLista= &(*pLista)->sig;
    }

    return REALIZADO;

}
void mostrarEntero(const void *dato)
{
    printf("El numero es: %d\n",*(int*)dato);
    //CASTEO EL PUNTERO A VOID A UN PUNTERO A INT Y MUESTRO SU CONTENIDO!!!
}
void mostrarChar(const void *dato)
{
    printf(" %c\n",*(char*)dato);
}
int mapV2(tLista *lista,Funcion accion)
{
    tLista *pLista;
    if(*lista==NULL)
    {
        printf("LA LISTA ESTA VACIA!\n");
        return LISTA_VACIA;
    }
    pLista=lista;
    while(*pLista!=NULL)
    {
        accion((*pLista)->dato,NULL);
        pLista= &(*pLista)->sig;
    }

    return REALIZADO;
}

void multiplicarPor3(void *dato, void *valor)
{
    *(int*)dato*=3;
}

void alCuadrado(void *dato, void *valor)
{
    *(int*)dato*= *(int*)dato;
}

void vaciarLista(tLista *lista)
{
    tNodo *aux;
    while(*lista!=NULL)
    {
        aux=*lista;
        *lista=aux->sig;
        free(aux->dato);
        free(aux);
    }
}

void mostrarListaInversa(tLista* lista, Mostrar mostrarDato)
{
    if (*lista == NULL)
        return;

    mostrarListaInversa(&(*lista)->sig, mostrarDato);

    mostrarDato((*lista)->dato);
}

void mostrarListaInversaItera(tLista* lista, Mostrar mostrarDato, unsigned tam)
{
    if (!lista || *lista == NULL)
        return;

    tLista pila;
    crearPila(&pila);

    tNodo *act = *lista;
    while (act)
    {
        apilar(&pila, act->dato, tam);
        act = act->sig;
    }

    void *datoAMostrar = malloc(tam);
    if (!datoAMostrar)
        return;

    while (!desapilar(&pila, datoAMostrar, tam))
    {
        mostrarDato(datoAMostrar);
    }

    free(datoAMostrar);
    vaciarPila(&pila);
}

