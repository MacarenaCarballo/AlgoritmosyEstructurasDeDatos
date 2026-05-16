#include "headerFinal.h"
void crearPila(tPila *pp)
{
    *pp=NULL;
}
void vaciarPila(tPila *pp)
{
    tNodo *elim;
    if(!*pp)
        return;
    while(*pp)
    {
        elim=*pp;
        *pp=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pp=NULL;
}

int apilar(tPila *pp, void *dato, unsigned tam)
{
    tNodo *nue;
    nue=malloc(sizeof(tNodo));
    if(!nue)
        return -1;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return -1;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pp;
    *pp=nue;
    return 0;
}
int pilaVacia(tPila *pp, void *dato, unsigned tam)
{
    if(*pp==NULL)
        return 0;
    else
        return 1;
}
int desapilar(tPila *pp, void *dato, unsigned tam)
{
    tNodo *elim;
    if(!*pp)
        return 1;
    elim=*pp;
    *pp=elim->sig;
    memcpy(dato,elim->dato,MINIMO(tam, elim->tam));
    free(elim->dato);
    free(elim);
    return 0;

}
int verTope(tPila *pp, void *dato, unsigned tam)
{
    if(!*pp)
        return 1;
    memcpy(dato,(*pp)->dato,MINIMO(tam,(*pp)->tam));
    return 0;
}
int validarXML(char *archivo)
{
    char linea[100];
    char *act;
    char etiqueta;
    char comparacion;
    tPila pila;


    crearPila(&pila);

    FILE *pf=fopen(archivo,"rt");
    if(!pf)
        return 1;

    while(fgets(linea,100,pf))
    {
        act=linea;
        while((act = strchr(act, '<')) != NULL)
        {
            act++;
            if(*act!='/')
            {
                etiqueta=*act;
                printf("GUARDO %c\n",etiqueta);
                apilar(&pila,&etiqueta,sizeof(char));
            }
            else
            {
                verTope(&pila,&comparacion,sizeof(char));
                printf("COMPARO %c\n",comparacion);
                act++;
                if(comparacion!=*act)
                {
                    fclose(pf);
                    vaciarPila(&pila);
                    return 1;
                }
                else
                    desapilar(&pila,&comparacion,sizeof(char));
            }
            act++;
            if(*act!='>')
            {
                fclose(pf);
                vaciarPila(&pila);
                return 1;
            }
            act++;
        }

    }
    fclose(pf);
    if(pilaVacia(&pila,&comparacion,4)!=0)//valido que no me queden etiquetas
    {
        vaciarPila(&pila);
        return 1;
    }

    vaciarPila(&pila);
    return 0;
}
int validarXMLExtenso(char *archivo, char *version)
{
    char linea[100];
    char *act, *fin,*guardo;
    char etiqueta[100];
    char comparacion[100];
    int longitud;
    tPila pila;
    crearPila(&pila);

    FILE *pf=fopen(archivo,"rt");
    if(!pf)
        return 1;

    if (fgets(linea, sizeof(linea), pf) == NULL)
    {
        fclose(pf);
        return 1;
    }
    if (sscanf(linea, "<?xml version=\"%[^\"]\"", version) != 1)
    {
        fclose(pf);
        return 1;
    }
    printf("Encabezado XML versión: %s\n", version);

    while(fgets(linea,100,pf))
    {
        act=linea;
        while((act = strchr(act, '<')) != NULL)
        {
            act++;
            if(*act!='/')
            {
                guardo=etiqueta;
                fin=strchr(act,'>');
                if(!fin)
                {
                    fclose(pf);
                    vaciarPila(&pila);
                    return 1;
                }
                while(act<fin)
                {
                    *guardo=*act;
                    act++;
                    guardo++;
                }
                *guardo='\0';
                printf("GUARDO %s\n",etiqueta);
                apilar(&pila,&etiqueta,sizeof(etiqueta)+1);
            }
            else
            {
                verTope(&pila,&comparacion,sizeof(comparacion));
                printf("COMPARO %s\n",comparacion);
                act++;
                fin=strchr(act,'>');
                if(!fin)
                {
                    fclose(pf);
                    vaciarPila(&pila);
                    return 1;
                }
                longitud=fin-act;
                strncpy(etiqueta,act,longitud);
                etiqueta[longitud]='\0';
                if(strcmp(comparacion,etiqueta)!=0)
                {
                    fclose(pf);
                    vaciarPila(&pila);
                    return 1;
                }
                else
                    desapilar(&pila,&comparacion,sizeof(comparacion));
            }
            act++;
//            if(*act!='>')
//            {
//                fclose(pf);
//                vaciarPila(&pila);
//                return 1;
//            }
        }

    }
    fclose(pf);
    if(pilaVacia(&pila,&comparacion,4)!=0)
    {
        vaciarPila(&pila);
        return 1;
    }

    vaciarPila(&pila);
    return 0;
}
