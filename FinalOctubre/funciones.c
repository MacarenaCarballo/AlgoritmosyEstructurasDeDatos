#include "final.h"
void crearLista(tLista *pl)
{
    *pl=NULL;
}

int insertarOrdenado(tLista *pl,  void *dato, unsigned tam, tCmp comparar, tAccion accion)
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
    while(*pl && comparar((*pl)->dato,dato)<0)
        pl=&(*pl)->sig;

    if(*pl && comparar((*pl)->dato,dato)==0)
    {
        free(nue->dato);
        free(nue);
        accion((*pl)->dato,dato);
        return 0;
    }

    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pl;
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
    while(*pl)
    {
        elim=*pl;
        *pl=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pl=NULL;
}
void mapeo(tLista *pl, tAccion accion)
{
    if(!*pl)
        return;
    while(*pl)
    {
        accion((*pl)->dato,NULL);
        pl=&(*pl)->sig;
    }
}
void mostrarLista(void *a, void *b)
{
    termino p1=*(termino *)a;
    printf("coef:%d poten: %d\n",p1.coeficiente,p1.potencia);
}

int bajarPolinomio(char *archivo, tLista *lista)
{
    char linea[50];
    int potencia, coeficiente;
    termino t;
    crearLista(lista);
    FILE *pf=fopen(archivo,"rt");
    if(!pf)
        return 1;
    while(fgets(linea, 50, pf))
    {
        // Parsear la línea: X(potencia)(coeficiente)
        if(sscanf(linea, "X(%d)(%d)", &potencia, &coeficiente) == 2)
        {
            t.potencia = potencia;
            t.coeficiente = coeficiente;
            insertarOrdenado(lista,&t,sizeof(termino),compararPotencia,sumarCoeficientes);
        }
    }
    fclose(pf);
    return 0;
}

int compararPotencia(const void *a, const void *b)
{
    termino p1=*(termino *)a;
    termino p2=*(termino *)b;
    return p1.potencia-p2.potencia;
}

void sumarCoeficientes(void *a, void *b)
{
    termino *p1 = (termino *)a;
    termino *p2 = (termino *)b;
    p1->coeficiente += p2->coeficiente;
}

int sumarPolinomios(tLista *p1, tLista *p2,tCmp comparar ,tAccion accion)
{
    FILE *pf=fopen("pResultado.txt","wt");
    if(!pf)
        return 1;
    while(*p1 && *p2)
    {
        if(comparar((*p1)->dato,(*p2)->dato)==0)
        {
            accion((*p1)->dato,(*p2)->dato);
            grabarArchivo((*p1)->dato,pf);
            p1=&(*p1)->sig;
            p2=&(*p2)->sig;
        }
        else if(comparar((*p1)->dato,(*p2)->dato)<0)
        {
            grabarArchivo((*p1)->dato,pf);
            p1=&(*p1)->sig;
        }else
        {
            grabarArchivo((*p2)->dato,pf);
            p2=&(*p2)->sig;
        }
    }
    while(*p1)
    {
        grabarArchivo((*p1)->dato,pf);
        p1=&(*p1)->sig;
    }
    while(*p2)
    {
        grabarArchivo((*p2)->dato,pf);
        p2=&(*p2)->sig;
    }
    fclose(pf);
    return 0;
}
void grabarArchivo(void *a, FILE *pf)
{
    termino p1 = *(termino *)a;
    fprintf(pf,"X(%d)(%d)\n",p1.potencia,p1.coeficiente);
}
