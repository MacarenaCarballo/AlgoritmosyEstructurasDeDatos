#include "headers.h"
void crear_tabla_puntos(t_tabla_puntos* p, unsigned tam)
{
    p->tam=tam;
    crearLista(&p->tabla);
}
int agregar_puntaje(t_tabla_puntos* p, const t_puntaje* dato)
{
    return insertarNodo(&p->tabla,dato,sizeof(t_puntaje),compararEnteros,p->tam);
}
void imprimir_tabla_puntos(t_tabla_puntos* p)
{
    mostrarLista(&p->tabla,mostrarEntero);
}
void vaciar_tabla_puntos(t_tabla_puntos* p)
{
    vaciarLista(&p->tabla);
    p->tam=0;
}

void crearLista(t_lista *pl)
{
    *pl=NULL;
}
int insertarNodo(t_lista *pl,const void *dato, unsigned tam, tCmp comparar, unsigned top)
{
    //PRIMERO BUSCO LA POSICION SIN PASARME DEL LIMITE y mientras alla lista
    unsigned cont=0;
    while(*pl && comparar((*pl)->dato,dato)>0 && cont<top)
    {
        cont++;
        pl=&(*pl)->sig;
    }
    if(cont>=top)//El dato es mayor no entra
        return 1;

    tNodo *nue=malloc(sizeof(tNodo));
    if(!nue)
        return ERROR;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return ERROR;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pl;
    *pl=nue;

    // Ahora eliminar el último si hay más de topN elementos
    cont = 0;
    t_lista *pAux = pl;
    while(*pAux && cont < top - 1)
    {
        cont++;
        pAux = &(*pAux)->sig;
    }

    // Si existe un nodo después de la posición topN-1, eliminarlo
    if(*pAux && (*pAux)->sig)
    {
        tNodo *aEliminar = (*pAux)->sig;
        (*pAux)->sig = NULL;
        free(aEliminar->dato);
        free(aEliminar);
    }

    return OK;
}

void vaciarLista(t_lista *pl)
{
    tNodo *elim;
    elim=*pl;
    while(*pl)
    {
        pl=&(*pl)->sig;
        free(elim->dato);
        free(elim);
        elim=*pl;
    }
    *pl=NULL;
}
int listaLlena(t_lista *pl, unsigned tam)
{
    return OK;
}
int listaVacia(t_lista *pl)
{
    if(*pl==NULL)
        return OK;
    return ERROR;
}
int compararEnteros(const void *a,const void *b)
{
    t_puntaje a1=*(t_puntaje*)a;
    t_puntaje b1=*(t_puntaje*)b;
    return a1.puntaje-b1.puntaje;
}
int mostrarLista(t_lista *lista, tAccion mostrarDato)
{
    t_lista *pLista;
    if(*lista==NULL)
    {
        printf("LA LISTA ESTA VACIA!\n");
        return 1;
    }
    pLista=lista;
    while(*pLista!=NULL)
    {
        mostrarDato((*pLista)->dato,NULL); //mostrar
        pLista= &(*pLista)->sig;
    }

    return OK;

}
void mostrarEntero(const void *dato, void *b)
{
    t_puntaje a1=*(t_puntaje*)dato;
    printf("El %s tiene: %d puntos\n",a1.iniciales,a1.puntaje);
    //CASTEO EL PUNTERO A VOID A UN PUNTERO A INT Y MUESTRO SU CONTENIDO!!!
}

int tablaPuntaje(char *nombre, t_tabla_puntos *tabla)
{
    FILE *pf=fopen(nombre,"rt");
    if(!pf)
        return 1;
    char linea[20], iniciales[4];
    int top,puntaje;
    t_puntaje reg;
//    t_puntaje vec[]={{"AAA",20},
//    {"ABA",10},
//    {"ACA",80}};
//    for(int i=0; i<3; i++)
//    {
//        agregar_puntaje(&tabla,&vec[i]);
//    }
    fgets(linea,20,pf);
    top=atoi(linea);
    crear_tabla_puntos(tabla,top);
    printf("%s",linea);
    while(fgets(linea,20,pf))
    {
        sscanf(linea,"%s %d",iniciales,&puntaje);
        printf("%s",linea);
        printf("%s %d\n",iniciales,puntaje);
        strcpy(reg.iniciales,iniciales);
        reg.puntaje=puntaje;
        agregar_puntaje(tabla,&reg);

    }
    fclose(pf);
    return 0;
}
