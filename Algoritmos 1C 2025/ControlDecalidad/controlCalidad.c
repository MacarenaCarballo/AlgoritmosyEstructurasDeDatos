#include "controlCalidad.h"
int cargarArchivoPrueba(char *nombArchivo)
{
    size_t i;
    FILE *pf=fopen(nombArchivo,"wt");
    if(!pf)
        return -1;
    tLote lotes[]= {{"L001", "1001", "OK"},
        {"L001", "1002", "FALLA"},
        {"L001", "1003", "OK"},
        {"L002", "2001", "FALLA"},
        {"L002", "2002", "FALLA"},
        {"L002", "2003", "OK"},
        {"L003", "3001", "OK"},
        {"L003", "3002", "OK"},
        {"L003", "3003", "FALLA"},
        {"L003", "3004", "OK"}
    };
    size_t n=(int)(sizeof(lotes)/sizeof(tLote));
    tLote *vec=lotes;

    for(i=0; i<n; i++)
    {
        fprintf(pf,"%s,%s,%s\n",vec->codLote,vec->idProd,vec->resulControl);
        vec++;

    }
    fclose(pf);
    return 0;
}

int bajarArchivo(char *archivo, tCola *cola)
{
    char linea[100];
    tLote registro;
    FILE *pf=fopen(archivo,"rt");
    if(!pf)
    {
        printf("No se pudo abrir el archivo\n");
        return -1;
    }
    while(fgets(linea, sizeof(linea), pf))
    {
        char *act = strchr(linea, '\n');
        if (act)
            *act = '\0';
        act=strrchr(linea,',');
        strcpy(registro.resulControl,act+1);

        *act='\0';
        act=strrchr(linea,',');
        strcpy(registro.idProd,act+1);

        *act='\0';
        strcpy(registro.codLote,linea);

        ponerEnCola(cola,&registro,sizeof(tLote));

    }

    fclose(pf);
    return 0;
}

int procesarEntrada(tCola *cola)
{
    tCola colaAux;
    tLote reg1;
    int flag=0;
    char lote[10];

    crearCola(&colaAux);
    sacarDeCola(cola,&reg1,sizeof(tLote));
    strcpy(lote,reg1.codLote);
    do
    {
        if(strcmpi(lote,reg1.codLote)==0)
        {
            if(strcmpi(reg1.resulControl,"FALLA")==0)
                flag=1;
            ponerEnCola(&colaAux,&reg1,sizeof(tLote));
            sacarDeCola(cola,&reg1,sizeof(tLote));
        }
        else
        {
            if(flag==1)
            {
                cargarArchivo("lotesObservados.txt",&colaAux);
                vaciarCola(&colaAux);
            }
            else
            {
                cargarArchivo("lotesAprobados.txt",&colaAux);
                vaciarCola(&colaAux);
            }
            ponerEnCola(&colaAux,&reg1,sizeof(tLote));
            strcpy(lote,reg1.codLote);
            flag=0;
        }
    }
    while(!colaVacia(cola));
    if(flag == 1)
        cargarArchivo("lotesObservados.txt", &colaAux);
    else
        cargarArchivo("lotesAprobados.txt", &colaAux);
    vaciarCola(&colaAux);

    return 0;
}
int cargarArchivo(char *archivo, tCola *cola)
{
    tLote reg;
    FILE *pa=fopen(archivo,"at");
    if(!pa)
        return -1;
    while(!colaVacia(cola))
    {
        sacarDeCola(cola,&reg,sizeof(tLote));
        fprintf(pa,"%s,%s,%s\n",reg.codLote,reg.idProd,reg.resulControl);
    }
    fclose(pa);
    return 0;
}
void crearCola(tCola *cola)
{
    cola->pri=0;
    cola->ult=0;
    cola->tam_disp=TAM_COLA;
}

int colaVacia(const tCola *cola)
{
    if(cola->tam_disp==TAM_COLA)
        return COLA_VACIA;
    else
        return COLA_NO_VACIA;
//    return cola->tam_disp==0;
}

void vaciarCola(tCola *cola)
{
    cola->pri=0;
    cola->ult=0;
    cola->tam_disp=TAM_COLA;
}

int colaLlena(const tCola *cola,unsigned tam)
{
    if(cola->tam_disp<tam+sizeof(unsigned))
        return COLA_LLENA;
    else
        return COLA_DISPONIBLE;
//   return cola->tam_disp<tam+sizeof(unsigned);
}

int ponerEnCola(tCola *cola,const void* dato,unsigned tam)
{
    unsigned ini,fin;
    if(cola->tam_disp<tam+sizeof(unsigned))
        return 0;//Cola llena
    cola->tam_disp-=tam+sizeof(unsigned);
    //EL MINIMO ENTRE LO QUE QUIERO PONER Y LO QUE TENGO DISPONIBLE AL FINAL DE LA COLA
    ini=MINIMO(TAM_COLA-cola->ult, sizeof(unsigned));
    if(ini!=0)
    {
        memcpy(cola->cola+cola->ult,&tam,ini);
    }
    fin=sizeof(unsigned)-ini;
    if(fin!=0)//SE TROZA EL DATO
    {
        //CASTEO A CHAR* PORQUE QUIERO QUE SE MUEVA CANTIDAD DE BYTES!!!!
        memcpy(cola->cola,(char*)&tam+ini,fin);
    }
    cola->ult=fin?fin:cola->ult+ini; //tambien puede ser cola->ult+sizeof(unsigned)


    //YA COPIE EL TAM DEL DATO POR QUE AHORA VUELVO A HACER TODO PARA LA INFO
    ini=MINIMO(TAM_COLA-cola->ult, tam);
    if(ini!=0)
    {
        memcpy(cola->cola+cola->ult,dato,ini);
    }
    fin=tam-ini;
    if(fin!=0)
        memcpy(cola->cola,(char*)dato+ini,fin);

    //ACOMODO EL ULTIMO
//    cola->ult=fin?fin:cola->ult+tam;
    cola->ult=fin?fin:cola->ult+ini;

    return REALIZADO;
}


int sacarDeCola(tCola *cola,void* dato,unsigned tam)
{
    unsigned ini,fin,tamInfo;
    if(cola->tam_disp==TAM_COLA)
        return COLA_VACIA;

    ini=MINIMO(TAM_COLA-cola->ult, sizeof(unsigned));

    if(ini!=0)
    {
        memcpy(&tamInfo,cola->cola+cola->pri,ini);
    }
    fin=sizeof(unsigned)-ini;
    if(fin!=0)
    {
        memcpy((char*)&tamInfo+ini,cola->cola,fin);
    }
    //SI FIN ES DISTINTO DE 0, PONGO EL PRI EN EL LUGAR DE FIN, SINO SUMO
    cola->pri=fin?fin:cola->pri+sizeof(unsigned);

    ini=MINIMO(TAM_COLA-cola->pri,tamInfo);

    if(ini!=0)
    {
        memcpy(dato,cola->cola+cola->pri,ini);
    }
    fin=tamInfo-ini;
    if(fin!=0)
    {
        memcpy((char*)dato+ini,cola->cola,fin);
    }
    cola->pri=fin?fin:cola->pri+ini;
    cola->tam_disp+=tamInfo+sizeof(unsigned);

    return REALIZADO;
}

int verPrimero (const tCola *cola,void* dato,unsigned tam)
{
    unsigned ini,fin,tamInfo;
    unsigned pos = cola->pri;

    if(cola->tam_disp==TAM_COLA)
        return COLA_VACIA;

    ini=MINIMO(TAM_COLA-cola->ult, sizeof(unsigned));

    if(ini!=0)
    {
        memcpy(&tamInfo,cola->cola+pos,ini);
    }
    fin=sizeof(unsigned)-ini;
    tamInfo=MINIMO(tam,tamInfo);
    if(fin!=0)
    {
        memcpy((char*)&tamInfo+ini,cola->cola,fin);
    }
    //PREGUNTO CON LA COPIA PARA NO MODIFICAR EL PUNTERO
    pos=fin?fin:pos+sizeof(unsigned);

    if(ini!=0)
    {
        memcpy(dato,cola->cola+pos,ini);
    }
    fin=tamInfo-ini;
    if(fin!=0)
    {
        memcpy((char*)dato+ini,cola->cola,fin);
    }

    return REALIZADO;
}
