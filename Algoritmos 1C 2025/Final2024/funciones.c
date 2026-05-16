#include "finalhead.h"
void preOrden(tArbol *pa, tAccion accion, void* param)
{
    if(!*pa)
        return;
    preOrden(&(*pa)->izq, accion, param);
    accion((*pa)->dato,accion);
    preOrden(&(*pa)->der, accion, param);
}

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
    *pa = NULL;
}

int insertarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar)
{
    tNodo *nue;
    if(!*pa)
    {
        nue=malloc(sizeof(tNodo));
        if(!nue)
            return -1;
        nue->dato=malloc(tam);
        if(!nue->dato)
        {
            free(nue);
            return -1;
        }
        nue->der=NULL;
        nue->izq=NULL;
        nue->tam=tam;
        memcpy(nue->dato,dato,tam);

        *pa=nue;
        return 0;
    }
    if(comparar(dato,(*pa)->dato)>0)
        return insertarNodo(&(*pa)->der,dato,tam,comparar);
    else if(comparar(dato,(*pa)->dato)<0)
        return insertarNodo(&(*pa)->izq,dato,tam,comparar);
    else
        return 2;
}

int crearLote(char *nombre)
{
    FILE *pf=fopen(nombre,"wt");
    if(!pf)
        return 1;
    tInfo vec[]=
    {
        {"L4",100},
        {"L2",100},
        {"L3",100},
        {"L1",100},
        {"L5",100},
        {"L6",100},
        {"L7",100},
        {"L8",100},
    };
    for(int i=0; i<8; i++)
        fprintf(pf,"%s|%d\n",vec[i].clave,vec[i].info);
    fclose(pf);
    return 0;
}

void mostrarArbol(void *dato, void*param)
{
    tInfo info=*(tInfo*)dato;
    printf("%s-%d\n",info.clave,info.info);
}

int bajarArchivo(char *nombre, tArbol *pa)
{
    tInfo reg;
    char linea[100];
    FILE *pf=fopen(nombre,"rt");
    if(!pf)
        return 1;
    while(fgets(linea,100,pf))
    {
        trozar(&reg,linea);
        insertarNodo(pa,&reg,sizeof(tInfo),compararStrings);
    }
    fclose(pf);
    return 0;
}

int compararStrings(void *a, void *b)
{
    tInfo info1=*(tInfo*)a;
    tInfo info2=*(tInfo*)b;
    return strcmpi(info1.clave,info2.clave);
}

void trozar(tInfo *inf, char *linea)
{
    char *act;
    act=strchr(linea,'\n');
    *act='\0';
    act=strrchr(linea,'|');
    inf->info=atoi(act+1);
    *act='\0';
    strcpy(inf->clave,linea);

}
int contarCantNodosPorNivel(tArbol *pa, int nivel)
{
    if(!*pa)
        return 0;
    if(nivel==0)
        return 1;
    return contarCantNodosPorNivel(&(*pa)->izq,nivel-1)+contarCantNodosPorNivel(&(*pa)->der,nivel-1);
}

int alturaArbol(tArbol *pa)
{
    int izq=0, der=0;
    if(!*pa)
        return 0;
    izq=alturaArbol(&(*pa)->izq);
    der=alturaArbol(&(*pa)->der);
    return (izq>der? izq:der)+1;
}

int potencia2(int nivel)
{
    int resultado = 1;
    for (int i = 0; i < nivel; i++)
        resultado *= 2;
    return resultado;
}

int esCompleto(tArbol *pa, int nivel)
{
    int potencia=potencia2(nivel);
    int cantNodos=contarCantNodosPorNivel(pa,nivel);
    if(cantNodos==0)
        return -1;
    else if(potencia==cantNodos)
        return 0;
    return potencia-cantNodos;
}
