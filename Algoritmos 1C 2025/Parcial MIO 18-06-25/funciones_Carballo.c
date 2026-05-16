#include "header_Carballo.h"

int crearLotePrueba(const char *nombreArch)
{
    tLote reg[10]= {{"L001",123,"OK"},
        {"L001",123,"FALLA"},
        {"L001",153,"FALLA"},
        {"L001",163,"FALLA"},
        {"L002",113,"OK"},
        {"L002",129,"OK"},
        {"L003",122,"OK"},
        {"L003",127,"OK"},
        {"L003",126,"FALLA"},
        {"L003",144,"OK"}
    };

    FILE *pf=fopen(nombreArch, "wb");
    if(!pf)
        return ERROR_COD;
    fwrite(&reg,sizeof(tLote),10,pf);
    fclose(pf);
    return REALIZADO;
}

int leerLote(const char *lote, tLista *pl)
{
    tLote reg;
    FILE *pf=fopen(lote, "rb");
    if(!pf)
        return ERROR_COD;

    while(fread(&reg,sizeof(tLote),1,pf))
    {
        // printf("COD LOTE: %s, ID PROD: %d, CONTROL: %s\n", reg.codLote, reg.idProd, reg.control);
        insertarOrdenado(pl,&reg,sizeof(tLote),comparoLote);
    }
    fclose(pf);
    return REALIZADO;
}

int insertarOrdenado(tLista *pl, void *dato, unsigned tam, tCmp comparar)
{
    tNodo *nue;
    while(*pl && comparar(dato, (*pl)->dato)>0)
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

void crearLista(tLista *pl)
{
    *pl=NULL;
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

int listaVacia(const tLista *pl)
{
    if(*pl==NULL)
        return VACIO;
    return REALIZADO;
}

int listaLlena(const tLista *pl)
{
    return REALIZADO;
}

int procesarArchivos(tLista *pl, tCmp comparar, char* archO, char *archA, int porcentaje, tCmp compararControl, tCmp compararIdProd)
{
    if(*pl==NULL)
    {
        puts("No hay archivos para procesar\n");
        return ERROR_COD;
    }
    tNodo *loteActual=*pl;
    int contTodos=0, contAprobados=0, calculo;
    FILE *pa=fopen(archA,"at");
    if(!pa)
        return ERROR_COD;

    FILE *po=fopen(archO,"at");
    if(!pa)
        return ERROR_COD;

    tLista aux, auxA;
    crearLista(&aux);
    crearLista(&auxA);
    while(*pl!=NULL)
    {
        while(*pl && comparar(loteActual->dato,(*pl)->dato)==0)
        {
            contTodos++;
            if(compararControl((*pl)->dato,"OK")==0)
            {
                insertarOrdenado(&auxA,(*pl)->dato,(*pl)->tam,compararIdProd);
                contAprobados++;
            }else
            {
                insertarOrdenado(&aux,(*pl)->dato,(*pl)->tam,compararIdProd);
            }

            pl=&(*pl)->sig;
        }
        if(contTodos!=0)
            calculo=(contAprobados*100)/contTodos;
        if(calculo>=porcentaje)
        {
            insertarArchivo(pa,&auxA);
            insertarArchivo(pa,&aux);
        }
        else
        {
           insertarArchivo(po,&aux);
            insertarArchivo(po,&auxA);
        }
        loteActual=*pl;
        contAprobados=0;
        contTodos=0;
        vaciarLista(&aux);
        vaciarLista(&auxA);
    }
    fclose(pa);
    fclose(po);
    return REALIZADO;
}

int comparoLote(const void *a, const void *b)
{
    tLote l1=*(tLote *)a;
    tLote l2=*(tLote *)b;
    return strcmpi(l1.codLote, l2.codLote);
}

int comparoControl(const void *a, const void *b)
{
    tLote l1=*(tLote *)a;
    char control[3]="OK";
    return strcmpi(l1.control, control);
}

int mapeo(tLista *pl, tAccion accion, void *dato)
{
    if(!*pl)
        return ERROR_COD;
    while(*pl)
    {
        accion((*pl)->dato,dato),
               pl=&(*pl)->sig;
    }
    return REALIZADO;
}

void mostrarLote(void *a, void *b)
{
    tLote reg=*(tLote *)a;
    printf("COD LOTE: %s, ID PROD: %d, CONTROL: %s\n", reg.codLote, reg.idProd, reg.control);
}

int comparoTodoOK(const void *a, const void *b)
{
    tLote l1=*(tLote *)a;
    tLote l2=*(tLote *)b;
    return l1.idProd-l2.idProd;
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
