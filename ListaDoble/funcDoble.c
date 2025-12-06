#include "headDoble.h"
void crearLista(tLista *pl)
{
    *pl=NULL;
}
int insertarOrdenado(tLista *pl, const void *dato, unsigned tam,tCmp comparar)
{
    tNodo *nue, *auxSig, *auxAnt, *act;
    if(!*pl)
    {
        auxAnt=NULL;
        auxSig=NULL;
    }
    else
    {
        act=*pl;
        while(act->ant && comparar(act->dato,dato)>0)
            act=act->ant;

        while(act->sig && comparar(act->dato,dato)<0)
            act=act->sig;

        if(comparar(act->dato,dato)==0)
            return 1;

        if(comparar(act->dato,dato)<0)
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
        return 1;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 1;
    }

    memcpy(nue->dato, dato, tam);
    nue->tam=tam;
    nue->sig=auxSig;
    nue->ant=auxAnt;

    if(auxSig)
        auxSig->ant=nue;
    if(auxAnt)
        auxAnt->sig=nue;
    *pl=nue;
    return 0;
}
int listaLlena(const tLista *pl, unsigned tam)
{
    return 0;
}
int listaVacia(const tLista *pl)
{
    if(*pl==NULL)
        return 0;
    return 1;
}
void vaciarLista(tLista *pl)
{
    tNodo *elim;
    while((*pl)->ant)
        pl=&(*pl)->ant;
    while(*pl)
    {
        elim=*pl;
        *pl=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pl=NULL;
}

int compararCaracteres(const void *a, const void *b)
{
    char a1=*(char*)a;
    char b1=*(char*)b;
    return a1-b1;
}

void mapeo(tLista *pl, tAccion accion)
{
    if(!*pl)
        return;
    while((*pl)->ant)
        pl=&(*pl)->ant;
    while(*pl)
    {
        accion((*pl)->dato,NULL);
        pl=&(*pl)->sig;
    }
}
int mostrarLista(void *a, void *b)
{
    char a1=*(char*)a;
    printf("%c\n",a1);
    return 0;
}
int eliminarNodo(tLista *pl, void *dato, unsigned tam,tCmp comparar)
{
    if(!*pl)
        return 1;
    tNodo *elim=*pl,*auxSig, *auxAnt;

    while(elim->ant)
        elim=elim->ant;

    while(elim->sig && comparar(elim->dato, dato)!=0)
        elim=elim->sig;

    if(comparar(elim->dato, dato)!=0 || elim==NULL)
        return 1;
    auxAnt=elim->ant;
    auxSig=elim->sig;
    free(elim->dato);
    free(elim);
    if(auxAnt)
        auxAnt->sig=auxSig;
    if(auxSig)
    {
        auxSig->ant=auxAnt;
        *pl=auxSig;
    }
    else
        *pl=auxAnt;
    return 0;

}
int filter(tLista *pl, tAccion filtro, void *param)
{
    if(!*pl)
        return 1;
    int flag;
    tNodo *elim=*pl, *auxSig, *auxAnt;
    while(elim->ant)
        elim=elim->ant;
    while(elim->sig)
    {
        auxAnt=elim->ant;
        auxSig=elim->sig;
        flag=filtro(elim->dato,param);
        if(flag==0)
        {
            free(elim->dato);
            free(elim);
            if(auxAnt)
                auxAnt->sig=auxSig;
            if(auxSig)
            {
                auxSig->ant=auxAnt;
            }
        }
          elim=elim->sig;
    }
    return 0;
}

int siEs(void *a, void*b)
{
    char dato=*(char*)a;
    char comp=*(char*)b;
    return dato-comp;
}
