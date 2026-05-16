#include "Ejercicio2.7Hibrido.h"
#include "head_Ejercicio2.7.h"
void crearPilaH(t_Pila* pila)
{
    pila->tope = TAM_PILA;
}


int apilarH(t_Pila *pila,const void *dato, unsigned tam)
{
    if(pila->tope == 0)
        return PILA_LLENA;

    t_Info * nueInfo = (t_Info*)malloc(sizeof(t_Info));

    if(!nueInfo)
        return SIN_MEM;

    nueInfo->dato = malloc(tam);

    if(!nueInfo->dato)
    {
        free(nueInfo);
        return SIN_MEM;
    }

    memcpy(nueInfo->dato, dato, tam);
    nueInfo->tam = tam;

    pila->elementos[pila->tope -1] = nueInfo;
    pila->tope--;

    return TODO_OK;
}

int desapilarH(t_Pila *pila, void * dato, unsigned tam)
{
    if(pila->tope == TAM_PILA)
        return PILA_VACIA;

    t_Info *elimInfo = pila->elementos[pila->tope];
    memcpy(dato,elimInfo->dato, MIN(tam,elimInfo->tam));

    free(elimInfo->dato);
    free(elimInfo);

    pila->tope++;

    return TODO_OK;
}


int verTopeH(const t_Pila *pila, void *dato, unsigned tam)
{
        if(pila->tope == TAM_PILA)
        return PILA_VACIA;

    t_Info *tope = pila->elementos[pila->tope];
    memcpy(dato,tope->dato, MIN(tam,tope->tam));

    return TODO_OK;
}

void vaciarPilaH(t_Pila *pila)
{
    while (pila->tope < TAM_PILA) {
        free(pila->elementos[pila->tope]->dato);
        free(pila->elementos[pila->tope]);
        pila->tope++;
    }
}


int pilaLlenaH(const t_Pila *pila)
{
    return pila->tope == 0;
}

int pilaVaciaH(const t_Pila *pila)
{
    return  pila->tope == TAM_PILA;
}

int sumaDosNumerosGrandeH(t_Pila* pila1, t_Pila *pila2, t_Pila* pilaRes)
{
    int acarreo=0;
    int num1,num2,suma,res;

    while(!pilaVaciaH(pila1)|| !pilaVaciaH(pila2)|| acarreo!=0)
    {
        if(pilaVaciaH(pila1))
            num1=0;
        else
            desapilarH(pila1,&num1,sizeof(int));


        if(pilaVaciaH(pila2))
            num2=0;
        else
            desapilarH(pila2,&num2,sizeof(int));


        suma=num1+num2+acarreo;
        res=suma%10;
        acarreo=suma/10;
        if (apilarH(pilaRes, &res, sizeof(int)) != SATISFACTORIO)
            return PILA_LLENA;
    }
    return SATISFACTORIO;
}

int prepararPilaH(t_Pila *pila, char *linea)
{
    int digito;
    if(*linea=='-')
    {
        printf("Numero negativo detectado, no aplica para la suma\n");
        return -1;
    }
    while(*linea)
    {
        if(ESDIGITO(*linea))
        {
            digito=charAentero(*linea);
            apilarH(pila,&digito,sizeof(int));
            printf("%d",digito);
        }

        linea++;
    }
    return SATISFACTORIO;
}

int subirArchivoTxtH(char * nombreArchivo,t_Pila *pila)
{
    int num;
    FILE *pf=fopen(nombreArchivo,"wt");
    if(!pf)
        return -1;

    while(!pilaVaciaH(pila))
    {
        desapilarH(pila,&num,sizeof(int));
        printf("%d",num);
        fprintf(pf,"%d",num);
    }
    fclose(pf);
    return SATISFACTORIO;
}
