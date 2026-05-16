#include "parcial.h"
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
int leerLote(char *nombreArch)
{
    FILE *pf=fopen(nombreArch,"rb");
    if(!pf)
        return ERRORCOD;
    tStock lote;

    puts("ENTRA\n");
    while(fread(&lote,sizeof(tStock),1,pf))
    {
        printf("COD PROD:%s  FECHA: %d,%d,%d  CANT: %d\n",lote.codProd,lote.fVto.dia,lote.fVto.mes,lote.fVto.anio,lote.cant);
    }
    fclose(pf);
    return REALIZADO;
}

void obtenerFecha(t_Fecha *act)
{
    time_t t=time(NULL);
    struct tm *tm_info = localtime(&t);
    act->dia=tm_info->tm_mday;
    act->mes=tm_info->tm_mon+1;
    act->anio=tm_info->tm_year+1900;
}

void crearLista(tLista *pl)
{
    *pl=NULL;
}

int insertarEnOrden(tLista *pl, void *dato, unsigned tam,tCmp comparar)
{
    while(*pl && comparar(dato,(*pl)->dato)>0)
        pl=&(*pl)->sig;

    tNodo *nue=malloc(sizeof(tNodo));
    if(!nue)
        return SIN_MEM;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pl;
    *pl=nue;
    return REALIZADO;

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

int compararEnteros(void *a, void *b)
{
    return *(int*)a-*(int*)b;
}
void mostrarEntero(void *a, void *b)
{
    printf("%d", *(int*)a);
}

int compararFechas(void *a, void *b)
{
    int d1,d2;

    tStock f1=*(tStock*)a;
    tStock f2=*(tStock*)b;

    d1=contarDias(f1.fVto.dia,f1.fVto.mes,f1.fVto.anio);
    d2=contarDias(f2.fVto.dia,f2.fVto.mes,f2.fVto.anio);
    if(d1-d2==0)
        return f2.cant-f1.cant;
    return d1-d2;

}

int mapeo(tLista *pl, tAccion accion, void *param)
{
    if(!*pl)
        return 0;
    while(*pl)
    {
        accion((*pl)->dato, param);
        pl=&(*pl)->sig;
    }
    return REALIZADO;
}

int bajarArchivo(char *nombreArch,tCmp comparar, tLista *pl, tAccion accion)
{
    FILE *pf=fopen(nombreArch,"rb");
    if(!pf)
        return ERRORCOD;
    tStock lote;

    while(fread(&lote,sizeof(tStock),1,pf))
    {
        if(contarDias(lote.fVto.dia,lote.fVto.mes,lote.fVto.anio)>0)
            insertarEnOrden(pl,&lote,sizeof(tStock),comparar);
    }
    mapeo(pl,accion,NULL);

    fclose(pf);
    return REALIZADO;
}


int productosAVencer(tLista *pl,tAccion accion,t_Fecha actF)
{
    int n;
    do
    {
        printf("Ingrese la cantidad de productos que desea procesar \n");
        scanf("%d",&n);
    }
    while(n<=0);
    tNodo *act=*pl;
    int nOrden=0;
    while(act && n>0)
    {
        accion(act->dato,&nOrden);
        act=act->sig;
        n--;
        nOrden++;
    }
    return REALIZADO;
}

int contarDias(int dia, int mes, int anio)
{
    t_Fecha act;
    obtenerFecha(&act);
    return ((anio*365)+(mes*30)+dia)-((act.anio*365)+(act.mes*30)+act.dia);//si ya paso la fecha es negativo
}

void mostrarMasproximo(tLista*pl)
{
    if(!*pl)
        return;
    mostrarStock((*pl)->dato,NULL);
}
void mostrarStock(void *a, void *b)
{
    tStock lote;
    if(a)
    {
        lote=*(tStock*)a;
        printf("Cod: %s|Descripcion: %s|Lote: %d|Fecha Vto: %02d/%02d/%d|Cant Stock: %d\n",lote.codProd,lote.descrip,lote.lote,lote.fVto.dia,lote.fVto.mes,lote.fVto.anio,lote.cant);
    }
}

void generarStock(void *a, void *b)
{
    if (!a || !b)
        return;

    tStock lote = *(tStock*)a;
    int nOrden = *(int*)b;

    FILE *pf = fopen("prod_a_vencer.txt", "at");
    if (!pf)
    {
        perror("Error al abrir el archivo");
        return;
    }

    if (fprintf(pf, "Nro Orden: %d|Cod: %s|Fecha Vto: %02d/%02d/%d|Cant Stock: %d\n",
                nOrden,
                lote.codProd,
                lote.fVto.dia,
                lote.fVto.mes,
                lote.fVto.anio,
                lote.cant) < 0)
    {
        perror("Error al escribir en el archivo");
    }

    fclose(pf);
}

