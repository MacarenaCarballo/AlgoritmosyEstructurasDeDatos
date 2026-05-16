#include "headAlgoritmos.h"
int generarLote(char *nombreArch)
{
    tStock lote[6]= {{"111111","yerba Mate",2,{24,06,2025},90},
        {"111112","yerba Mate",3,{30,06,2025},55},
        {"111113","azucar",8,{01,07,2025},70},
        {"111114","sal",10,{26,06,2025},60},
        {"111115","comino",1,{29,06,2025},100},
        {"111116","avena",6,{10,06,2025},20}
    };

    FILE *pf=fopen(nombreArch,"wb");
    if(!pf)
        return ERRORCOD;
    fwrite(&lote,sizeof(tStock),6,pf);
    fclose(pf);
    return REALIZADO;

}

int leerLote(char *nombreArch,tArbol *pa,tCmp comparar)
{
    FILE *pf=fopen(nombreArch,"rb");
    if(!pf)
        return ERRORCOD;
    tStock lote;
    tIndice ind;
    int pos=0;
    while(fread(&lote,sizeof(tStock),1,pf))
    {
        strcpy(ind.codProd,lote.codProd);
        ind.pos=pos;
        insertarNodo(pa,&ind,sizeof(tIndice),comparar,NULL,NULL);
        printf("COD PROD:%s  FECHA: %d,%d,%d  CANT: %d\n",lote.codProd,lote.fVto.dia,lote.fVto.mes,lote.fVto.anio,lote.cant);
        pos++;

    }
    fclose(pf);
    return REALIZADO;
}

void crearArbol(tArbol *pa)
{
    *pa=NULL;
}


int insertarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar, tAccion accion, void *param)
{
    if(!*pa)
    {
        tNodo *nue=malloc(sizeof(tNodo));
        if(!nue)
            return ERRORCOD;
        nue->dato=malloc(tam);
        if(!nue->dato)
        {
            free(nue);
            return ERRORCOD;
        }
        memcpy(nue->dato,dato,tam);
        nue->tam=tam;
        nue->izq=NULL;
        nue->der=NULL;

        *pa=nue;
        return REALIZADO;
    }
    int cmp;
    if((cmp=comparar((*pa)->dato,dato))<0)
        return insertarNodo(&(*pa)->der,dato,tam,comparar,accion,param);
    else if(cmp>0)
        return insertarNodo(&(*pa)->izq,dato,tam,comparar,accion,param);
    else
    {
         if(accion!=NULL)
        accion((*pa)->dato,param);
        return DUPLICADO;
    }

}

int alturaArbol(const tArbol *pa)
{
    int izq=0,der=0;
    if(!*pa)
        return 0;
    izq=alturaArbol(&(*pa)->izq);
    der=alturaArbol(&(*pa)->der);

    return 1+(izq>der?izq:der);

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

int compararCodProd(void *a, void*b)
{
    tIndice Ind1=*(tIndice*)a;
    tIndice Ind2=*(tIndice*)b;
    return strcmpi(Ind1.codProd,Ind2.codProd);
}

int mostrarCodProd(void *a, void*b)
{
    tIndice cod=*(tIndice*)a;
    printf("COD:%s| POS: %d\n",cod.codProd,cod.pos);
    return REALIZADO;
}

void recorrerInOrden(tArbol *pa,tAccion accion)
{
    int pos=0;
    if(!*pa)
        return ;
    recorrerInOrden(&(*pa)->izq,accion);
    if(accion((*pa)->dato,&pos)!=REALIZADO)
        return;
    recorrerInOrden(&(*pa)->der,accion);
}

int crearIndice(void *dato, void *param)
{
    FILE *pf=fopen("Indice.idx","ab");
    if(!pf)
        return ERRORCOD;

    tIndice lote=*(tIndice*)dato;

    fwrite(&lote,sizeof(tIndice),1,pf);

    fclose(pf);
    return REALIZADO;
}

int leerIndice(const char *nombreIndice)
{
    FILE *pf = fopen(nombreIndice, "rb");
    if (!pf)
    {
        perror("No se pudo abrir el archivo de índice");
        return ERRORCOD;
    }

    tIndice ind;
    printf("Contenido del archivo %s:\n", nombreIndice);
    printf("-------------------------------------\n");

    while (fread(&ind, sizeof(tIndice), 1, pf) == 1)
    {
        printf("CodProd: %s  Pos: %d\n", ind.codProd, ind.pos);
    }

    fclose(pf);
    return REALIZADO;
}

int eliminarNodo(tArbol *pa, void *dato, unsigned tam, tCmp comparar, tAccion accion, void *param)
{
    if(!*pa)
        return ERRORCOD;

    tArbol *elim=buscarClave(pa,comparar,dato);
    if(!*elim)
    {
       puts("No se encontro el nodo a eliminar\n");
       return ERRORCOD;
    }
    if((*elim)->der ==NULL && (*elim)->izq)
    {
        free((*elim)->dato);
        free(*elim);
        *elim=NULL;
        return REALIZADO;
    }
    void *datoAux;
    unsigned tamAux;
    tArbol *paR;
    tArbol nodoAEliminar;
    int altIzq, altDer;
    altIzq=alturaArbol(&(*elim)->izq);
    altDer=alturaArbol(&(*elim)->der);
    if(altDer>altIzq)
    {
        paR=&(*elim)->der;
        while((*paR)->izq)
            paR=&(*paR)->izq;
    }else
    {
        paR=&(*elim)->izq;
        while((*paR)->der)
            paR=&(*paR)->der;
    }
    nodoAEliminar=*paR;
    datoAux=(*elim)->dato;
    tamAux=(*elim)->tam;
    (*elim)->dato=(*paR)->dato;
    (*elim)->tam=(*paR)->tam;
    (*paR)->dato=datoAux;
    (*paR)->tam=tamAux;

    if((*pa)->der)
        *pa=(*pa)->der;
    else
        *pa=(*pa)->izq;

    free(nodoAEliminar->dato);
    free(nodoAEliminar);

    return REALIZADO;
}

tArbol *buscarClave(tArbol *pa,tCmp comparar, void *clave)
{
    if(!*pa)
        return NULL;
    int cmp;
    if((cmp=comparar(clave,(*pa)->dato))==0)
        return pa;
    else if(cmp<0)
        return buscarClave(&(*pa)->izq,comparar,clave);
    else
        return buscarClave(&(*pa)->der,comparar,clave);
}

int balancear(FILE *pf,int ini ,int fin, tArbol *pa)
{
    if(ini>fin)
        return 1;
    int medio=(ini+fin)/2;
    tIndice ind;
    fseek(pf,sizeof(tIndice)*medio,0);
    fflush(pf);
    fread(&ind,sizeof(tIndice),1,pf);
   // printf("COD:%s| POS: %d\n",ind.codProd,ind.pos);
    insertarNodo(pa,&ind,sizeof(tIndice),compararCodProd,NULL,NULL);
    balancear(pf,ini,medio-1,pa);
    balancear(pf,medio+1,fin,pa);
    return REALIZADO;

}

int compararNada(void *a, void *b)
{
    return 1;
}
