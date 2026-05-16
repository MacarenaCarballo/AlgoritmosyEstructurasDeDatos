#include "head.h"
void crearCola(tCola *pc)
{
    pc->pri=NULL;
    pc->ult=NULL;
}

int encolar(tCola *pc, void *dato, unsigned tam)
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
    memcpy(nue->dato,dato, tam);
    nue->tam=tam;
    nue->sig=NULL;
    if(pc->pri==NULL)
        pc->pri=nue;
    else
        pc->ult->sig=nue;//AL SIGUIENTE DEL ULTIMO LE ENGANCHO EL NUEVO

    pc->ult=nue;
    return REALIZADO;

}

int desencolar(tCola *pc, void *dato, unsigned tam)
{
    if(!pc->pri)
        return ERRORCOD;

    tNodo *elim=pc->pri;
    pc->pri=elim->sig;

    if(!pc->pri) //Si el siguiente es nulo, no hay mas cola
        pc->ult=NULL;

    memcpy(dato, elim->dato, MINIMO(elim->tam,tam));
    free(elim->dato);
    free(elim);
    return REALIZADO;
}

void vaciarCola(tCola *pc)
{
    tNodo *elim;
    while(pc->pri)
    {
        elim=pc->pri;
        pc->pri=elim->sig;
        free(elim->dato);
        free(elim);

    }
    pc->ult=NULL;
    pc->pri=NULL;
}

int procesarArchivoTxt(const char *nombreArch, tCola *pc)
{
    FILE *pf=fopen(nombreArch,"rt");
    if(!pf)
        return ERRORCOD;
    char linea[100];
    Empleado emp;
    printf("Entra\n");
    while(fgets(linea,100,pf))
    {

        trozado(linea,&emp);
        encolar(pc,&emp,sizeof(Empleado));
        printf("%s,%s,%.02f,%d/%d/%d\n",emp.nombre,emp.dni,emp.sueldo,emp.fechaIngreso.dia,emp.fechaIngreso.mes,emp.fechaIngreso.anio);
    }
    fclose(pf);
    return REALIZADO;
}

int trozado(char *linea, Empleado* emp)
{
    char *act;
    act=strchr(linea,'\n');
    *act='\0';

    act=strrchr(linea,'/');
    emp->fechaIngreso.anio=atoi(act+1);

    *act='\0';
    act=strrchr(linea,'/');
    emp->fechaIngreso.mes=atoi(act+1);


    *act='\0';
    act=strrchr(linea,',');
    emp->fechaIngreso.dia=atoi(act+1);

    *act='\0';
    act=strrchr(linea,',');
    emp->sueldo=atof(act+1);

    *act='\0';
    act=strrchr(linea,',');
    strcpy(emp->dni,act+1);

    *act='\0';
    strcpy(emp->nombre,linea);


    return REALIZADO;
}
