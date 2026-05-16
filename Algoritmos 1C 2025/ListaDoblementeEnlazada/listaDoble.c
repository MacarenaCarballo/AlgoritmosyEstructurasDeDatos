#include "listaDoble.h"

void crearLista(tLista *lista)
{
    *lista=NULL;
}

int insertarNodo(tLista *lista, void * dato, unsigned tam, tComparar comparar,Funcion accion, void *arg)
{
    tNodo *auxSig, *auxAnt, *act,*nue;
    if(*lista==NULL)
    {
        auxAnt=NULL;
        auxSig=NULL;
    }
    else
    {
        act=*lista;
        while(act->sig && comparar(act->dato, dato)<0)
            act=act->sig;

        while(act->ant && comparar(act->dato, dato)>0)
            act=act->ant;

        if(comparar(act->dato, dato)==0)
        {
            if(accion)
                accion(act->dato,arg);
            *lista=act;
            return DUPLICADO;//SINO PUEDO PONER ACCION
        }


        else if(comparar(act->dato, dato)<0)
        {
            auxAnt=act;
            auxSig=act->sig;
        }
        else
        {
            auxAnt=act->ant;
            auxSig=act;
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

    memcpy(nue->dato, dato, tam);
    nue->tam=tam;
    nue->sig=auxSig;
    nue->ant=auxAnt;

    if(auxAnt!=NULL)
        auxAnt->sig=nue;
    if(auxSig!=NULL)
        auxSig->ant=nue;

    *lista=nue;

    return REALIZADO;
}

int filter(tLista *lista,tFiltro filtro, void *param)
{
    tNodo *act=*lista;
    tNodo *auxSig, *auxAnt,*elim;
    if(!lista || *lista==NULL)
        return -2;

    while(act->ant)
        act=act->ant;

    while(act->sig)
    {
        auxAnt=act->ant;
        auxSig=act->sig;
        if(filtro(act->dato,param)==0)
        {
            elim=act;
            if(auxAnt)
                auxAnt->sig=auxSig;

            if(auxSig)
                auxSig->ant=auxAnt;
            free(elim->dato);
            free(elim);
        }
        act=act->sig;
    }

    return REALIZADO;
}
int borrarPares(void *dato, void *param)
{
    return *(int*)dato%2;
}
int mostrarListaFinal(tLista *lista, Funcion accion)
{
    tNodo *act;
    if(*lista==NULL)
        return -1;

    act=*lista;
    while(act->sig)
        act=act->sig;

    while(act->ant)
    {
        accion(act->dato,NULL);
        act=act->ant;
    }
    accion(act->dato,NULL);
    return REALIZADO;
}
int mostrarListaPrincipio(tLista *lista, Funcion accion)
{
    tNodo *act;
    if(*lista==NULL)
        return -1;

    act=*lista;
    while(act->ant)
        act=act->ant;

    while(act->sig)
    {
        accion(act->dato,NULL);
        act=act->sig;
    }
    accion(act->dato,NULL);
    return REALIZADO;
}
void mostrarEntero(void *dato, void *dato2)
{
    int num=*(int*)dato;
    printf("EL NUMERO ES: %d\n",num);
}
int compararEnteros(void *dato1, void *dato2)
{
    return *(int*)dato1-*(int *)dato2;
}

void vaciarLista(tLista *lista)
{
    tNodo *elim,*act;
    act=*lista;
    while(act->ant)
        act=act->ant;
    while(act->sig)
    {
        elim=act;
        act=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *lista=NULL;
}

int listaLlena(tLista *lista, unsigned tam)
{
    return 0;
}

int eliminarNodo(tLista *lista, void * dato, unsigned tam, tComparar comparar)
{
    tNodo *elim, *auxSig, *auxAnt;
    elim=*lista;
    if(*lista==NULL)
        return -4;

    while(elim->sig && comparar(elim->dato,dato)<0)
        elim=elim->sig;
    while(elim->ant && comparar(elim->dato,dato)>0)
        elim=elim->ant;

    if(comparar(elim->dato,dato)!=0)
        return NO_ENCONTRADO;

    auxAnt=elim->ant;
    auxSig=elim->sig;

    if(auxAnt!=NULL)
        auxAnt->sig=auxSig;
    if(auxSig!=NULL)
    {
        auxSig->ant=auxAnt;
        *lista=auxAnt;
    }else
        *lista=auxSig;

    memcpy(dato, elim->dato,MINIMO(tam, elim->tam));

    free(elim->dato);
    free(elim);

    return REALIZADO;


}
int listaVacia(tLista *lista)
{
    if(*lista==NULL)
        return 0;
    else
        return 1;
}


