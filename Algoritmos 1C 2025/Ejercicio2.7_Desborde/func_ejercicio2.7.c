#include "head_Ejercicio2.7.h"
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

int charAentero(char cad)
{
    if(cad>='0' && cad<='9')
        return cad-'0';
    return -1;
}

int bajarArchivoTxt(char * nombreArchivo, char *linea)
{
    FILE *pf=fopen(nombreArchivo,"rt");
    if(!pf)
    {
        printf("La apertura del archivo fallo\n");
        return -3;
    }
//    char* linea=(char*)malloc(TAM_CAD);
//    if(!linea)
//        return -3;

    fgets(linea,TAM_CAD,pf);
    linea[strcspn(linea, "\n")] = '\0';
    fclose(pf);
    return SATISFACTORIO;
}

int sumaDosNumerosGrande(tPila* pila1, tPila *pila2, tPila* pilaRes)
{
    int acarreo=0;
    int num1,num2,suma,res;

    while(!pilaVacia(pila1)|| !pilaVacia(pila2)|| acarreo!=0)
    {
        if(pilaVacia(pila1))
            num1=0;
        else
            desapilar(pila1,&num1,sizeof(int));


        if(pilaVacia(pila2))
            num2=0;
        else
            desapilar(pila2,&num2,sizeof(int));

        suma=num1+num2+acarreo;
        res=suma%10;
        acarreo=suma/10;
        if (apilar(pilaRes, &res, sizeof(int)) != SATISFACTORIO)
            return PILA_LLENA;
    }
    return SATISFACTORIO;
}

int prepararPila(tPila *pila, char *linea)
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
            apilar(pila,&digito,sizeof(int));
            printf("%d",digito);
        }

        linea++;
    }
    return SATISFACTORIO;
}

int subirArchivoTxt(char * nombreArchivo,tPila *pila)
{
    int num;
    FILE *pf=fopen(nombreArchivo,"wt");
    if(!pf)
        return -1;

    while(!pilaVacia(pila))
    {
        desapilar(pila,&num,sizeof(int));
        printf("%d",num);
        fprintf(pf,"%d",num);
    }
    fclose(pf);
    return SATISFACTORIO;
}
