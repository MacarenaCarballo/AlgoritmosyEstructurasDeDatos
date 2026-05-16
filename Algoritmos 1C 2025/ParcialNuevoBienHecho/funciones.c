#include "header.h"
int crearLotePrueba(const char *nombreArch)
{
    tLote reg[]= {{"L001",123,"OK"},
        {"L001",123,"FALLA"},
        {"L001",153,"FALLA"},
        {"L001",163,"FALLA"},
        {"L002",113,"OK"},
        {"L002",129,"OK"},
        {"L003",122,"OK"},
        {"L003",127,"OK"},
        {"L003",126,"FALLA"},
        {"L004",154,"OK"},
        {"L004",164,"OK"},
        {"L004",194,"OK"},
        {"L005",124,"FALLA"}

    };

    FILE *pf=fopen(nombreArch, "wb");
    if(!pf)
        return ERROR_COD;
    fwrite(&reg,sizeof(tLote),sizeof(reg)/sizeof(tLote),pf);
    fclose(pf);
    return REALIZADO;
}

int leerLote(const char *lote)
{
    tLote reg;
    FILE *pf=fopen(lote, "rb");
    if(!pf)
        return ERROR_COD;

    while(fread(&reg,sizeof(tLote),1,pf))
    {
        printf("COD LOTE: %s, ID PROD: %d, CONTROL: %s\n", reg.codLote, reg.idProd, reg.control);
    }
    fclose(pf);
    return REALIZADO;
}
void mostrarMenu()
{
    puts("BIENVENIDO AL PROGRAMA DE PROCESAMIENTO\n");
    puts("SELECCIONE UNA OPCION PARA CONTINUAR....\n");
    puts("********************************************\n");
    puts("1- Elija un porcentaje para analizar los lotes\n");
    puts("2- Procesar el archivo de entrada\n");
    puts("3- Mostrar el archivo de entrada\n");
    puts("4- Mostrar los archivos de salida\n");
    puts("5- Salir\n");
}

int mostrarArchivos(char *titulo, char *nombreArchivo, int porcentaje)
{
    FILE *pf=fopen(nombreArchivo, "rt");
    if(!pf)
        return ERROR_COD;
    char linea[100];
    printf("ARCHIVO CON LOS LOTES %s RESPECTO DEL PORCENTAJE %d\n",titulo,porcentaje);
    puts("******************************************************\n");
    printf("COD LOTE|IDPROD|CONTROL.\n");
    tLote reg;
    while(fgets(linea,100,pf))
    {
        trozado(linea,&reg);
        printf("%s  |%5d|%s\n", reg.codLote, reg.idProd, reg.control);
    }
    return REALIZADO;
}
void trozado(char *linea, tLote*reg)
{
    char *act;
    act=strchr(linea,'\n');
    *act='\0';

    act=strrchr(linea,'|');
    strcpy(reg->control,act+1);

    *act='\0';
    act=strrchr(linea,'|');
    reg->idProd=atoi(act+1);

    *act='\0';
    strcpy(reg->codLote,linea);
}

void crearLista(tLista *pl)
{
    *pl=NULL;
}

void vaciarLista(tLista *pl)
{
    tNodo *elim;
    if(!*pl)
        return;
    while(*pl)
    {
        elim=*pl;
        *pl=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pl=NULL;
}

int insertarOrdenado(tLista *pl, tCmp comparar, void *dato, unsigned tam)
{
    tNodo *nue;

    while(*pl && comparar((*pl)->dato, dato)<0)
        pl=&(*pl)->sig;

    nue=malloc(sizeof(tNodo));
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
    nue->sig=*pl;

    *pl=nue;
    return REALIZADO;

}

int compararId(const void *a, const void *b)
{
    tLote n1=*(tLote*)a;
    tLote n2=*(tLote*)b;
    return n1.idProd-n2.idProd;
}

int procesarArchivos(const char *nombreAprobados, const char *nombreObservados, int porcentaje, const char *nombreEntrada)
{
    float calculo;
    FILE *pAprobados, *pObservados, *pEntrada;
    tLista listaOk, listaFalla;
    tLote regAct;
    char loteActual[TAM_LOTE];
    int contAprobados=0, contTodos=0;

    pAprobados=fopen(nombreAprobados,"at");
    if(!pAprobados)
        return ERROR_COD;

    pObservados=fopen(nombreObservados,"at");
    if(!pObservados)
    {
        fclose(pAprobados);
        return ERROR_COD;
    }

    pEntrada=fopen(nombreEntrada,"rb");
    if(!pEntrada)
    {
        fclose(pAprobados);
        fclose(pObservados);
        return ERROR_COD;
    }
    crearLista(&listaFalla);
    crearLista(&listaOk);

    fread(&regAct,sizeof(tLote),1,pEntrada);
    strcpy(loteActual,regAct.codLote);

    while(!feof(pEntrada))
    {
        while(!feof(pEntrada) && strcmpi(loteActual,regAct.codLote)==0)
        {
            if(strcmpi(regAct.control,"OK")==0)
            {
                contAprobados++;
                insertarOrdenado(&listaOk,compararId,&regAct,sizeof(tLote));
            }
            else
            {
                insertarOrdenado(&listaFalla,compararId,&regAct,sizeof(tLote));
            }

            contTodos++;
            fread(&regAct,sizeof(tLote),1,pEntrada);
        }
        if(contTodos!=0)
        {
            calculo=((float)contAprobados*100.00)/contTodos;
            printf("PORCENTAEJE CALCULADO %f\n",calculo);
        }
        if(calculo>(float)porcentaje)
        {
            insertarArchivo(pAprobados,&listaOk);
            insertarArchivo(pAprobados,&listaFalla);
        }else
        {
            insertarArchivo(pObservados,&listaFalla);
            insertarArchivo(pObservados,&listaOk);
        }
        vaciarLista(&listaFalla);
        vaciarLista(&listaOk);
        contAprobados=0;
        contTodos=0;
        strcpy(loteActual,regAct.codLote);
    }
    fclose(pAprobados);
    fclose(pObservados);
    fclose(pEntrada);
    vaciarLista(&listaFalla);
    vaciarLista(&listaOk);

    return REALIZADO;
}

void insertarArchivo(FILE *pf, tLista *pl)
{
    if(!*pl)
        return;
    tLote reg;
    while(*pl)
    {
        reg=*(tLote*)(*pl)->dato,
        fprintf(pf,"%s|%d|%s\n",reg.codLote,reg.idProd,reg.control);
        pl=&(*pl)->sig;
    }
}
