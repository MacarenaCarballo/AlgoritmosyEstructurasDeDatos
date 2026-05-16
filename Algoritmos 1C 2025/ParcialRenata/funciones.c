#include "head.h"
int crearLote(char *nombre)
{
    Registro reg[7]=
    {
        {"AB123CD",900,"Macarena Carballo", 46585025,{2024,05,13},20400.5},
        {"AC123CD",920,"Macarena Carballo", 45862502,{2024,05,15},20400.5},
        {"AH123CD",960,"Macarena Fernandez", 4222336,{2024,05,13},20400.5},
        {"AF123CD",9050,"Macarena Carballo", 12345678,{2024,05,12},20400.5},
        {"AB123CD",9020,"Macarena Carballo", 46585025,{2024,05,13},20400.5},
        {"AC123CD",9010,"Macarena Lopez", 45862502,{2024,05,13},20400.5},
        {"AP123CD",90091,"Macarena Ramirez", 46585025,{2024,05,11},20400.5},
    };

    FILE *pf=fopen(nombre,"wb");
    if(!pf)
        return ERRORCOD;

    fwrite(&reg,sizeof(Registro),7,pf);

    fclose(pf);
    return REALIZADO;
}

int leerArchivo(char *nombre,tLista *pl)
{
    Registro reg;
    FILE *pf=fopen(nombre,"rb");
    if(!pf)
        return ERRORCOD;

    while(fread(&reg,sizeof(Registro),1,pf))
    {
        //printf("DNI: %d, PATENTE: %s, DEUDA: %f, FECHA VTO: %04d/%02d/%02d\n",reg.dni,reg.patente,reg.importe,reg.vto.a,reg.vto.m,reg.vto.d);
        insertarNodo(pl,&reg,sizeof(Registro),compararDniyPatente);
    }
    fclose(pf);
    return REALIZADO;
}

int compararDni(void *a, void *b)
{
    Registro n1=*(Registro*)a;
    Registro n2=*(Registro*)b;
    return n1.dni-n2.dni;
}

int compararDniyPatente(void *a, void *b)
{
    Registro n1=*(Registro*)a;
    Registro n2=*(Registro*)b;
    if(n1.dni==n2.dni)
         return strcmp(n1.patente, n2.patente);
    return n1.dni-n2.dni;
}

void crearLista(tLista *pl)
{
    *pl=NULL;
}

int insertarNodo(tLista *pl, void *dato, unsigned tam, tCmp comparar)
{
    tNodo *auxAnt, *auxSig, *act, *nue;


    if(*pl==NULL)
    {
        auxAnt=NULL;
        auxSig=NULL;
    }
    else
    {
        act=*pl;
        while(act->ant && comparar(act->dato,dato)>0)
            act=act->ant;

        while(act->sig && comparar(act->dato,dato)<0)
            act=act->sig;

        //PREGUNTO DONDE ME QUEDE
        if(comparar(act->dato,dato)<0)
        {
            auxAnt=act;
            auxSig=act->sig;
        }
        else
        {
            auxAnt=act->ant;
            auxSig=act;
        }

    }
    nue=malloc(sizeof(tNodo));
    if(!nue)
        return ERRORCOD;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return ERRORCOD;
    }
    memcpy(nue->dato, dato, tam);
    nue->tam=tam;
    nue->ant=auxAnt;
    nue->sig=auxSig;

    if(auxAnt)
        auxAnt->sig=nue;
    if(auxSig)
        auxSig->ant=nue;

    *pl=nue;
    return REALIZADO;

}

void vaciarLista(tLista *pl)
{
    tNodo *act=*pl, *elim;
    if(*pl==NULL)
        return;
    while(act->ant)
        act=act->ant;
    while(act)
    {
        elim=act;
        act=elim->sig;
        free(elim->dato);
        free(elim);
    }
    *pl=NULL;
}

int filter(tLista *pl, tCmp comparar, tAccion accion, void *dato, void *param)
{
    tNodo *act=*pl;

    while(act->ant)
        act=act->ant;

    while(act)
    {
        if(comparar(act->dato,dato)==0)
            accion(act->dato,param);
        act=act->sig;
    }

    return REALIZADO;
}

int crearDeuda(void *a, void *b)
{
    tLista *act=(tLista*)b;
    Registro deuda=*(Registro*)a;
    insertarNodo(act,&deuda,sizeof(Registro),compararImporte);
    return REALIZADO;
}
int compararImporte(void *a, void *b)
{
    Registro n1=*(Registro*)a;
    Registro n2=*(Registro*)b;
    if(n1.importe > n2.importe)
        return 1;
    if(n1.importe < n2.importe)
        return -1;
    return 0;

}

float deudaTotal(tLista *pl)
{
    tNodo *act=*pl;
    Registro deu;
    float sumaTotal=0;
    while(act->ant)
        act=act->ant;
    while(act)
    {
        deu=*(Registro*)act->dato;
        sumaTotal+=deu.importe;
        act=act->sig;
    }
    return sumaTotal;
}

int cargarArchivoDNI(tLista *pl, FILE *pf, float deudaTotal)
{
    tNodo *act=*pl;
    Registro deu;

    while(act->ant)
        act=act->ant;

    while(act)
    {
        deu=*(Registro*)act->dato;
        fprintf(pf,"|%d|%f|\n",deu.dni,deu.importe);
        act=act->sig;
    }
    fprintf(pf,"LA DEUDA TOTAL ES: %f",deudaTotal);
    return REALIZADO;
}

int cargarArchivoDNIyPatente(tLista *pl, FILE *pf, float deudaTotal)
{
    tNodo *act=*pl;
    Registro deu;

    while(act->ant)
        act=act->ant;

    while(act)
    {
        deu=*(Registro*)act->dato;
        fprintf(pf,"|%d|%s|%f|\n",deu.dni,deu.patente,deu.importe);
        act=act->sig;
    }
    fprintf(pf,"LA DEUDA TOTAL ES: %f",deudaTotal);
    return REALIZADO;
}
int mostrarListaPrincipio(tLista *lista, tAccion accion)
{
    tNodo *act;
    if(*lista==NULL)
        return -1;

    act=*lista;
    while(act->ant)
        act=act->ant;

    while(act->sig)
    {
        accion(act->dato,NULL);
        act=act->sig;
    }
    accion(act->dato,NULL);
    return REALIZADO;
}
int mostrarReg(void *a, void *b)
{
    Registro reg=*(Registro*)a;
     printf("DNI: %d, PATENTE: %s, DEUDA: %f, FECHA VTO: %04d/%02d/%02d\n",reg.dni,reg.patente,reg.importe,reg.vto.a,reg.vto.m,reg.vto.d);
     return REALIZADO;
}

int compararDniEspecifico(void *a, void *b)
{
    Registro reg = *(Registro*)a;
    int dniBuscado = *(int*)b;
    return reg.dni - dniBuscado;
}

 int compararDniyPatenteEspecifico(void *a, void *b)
 {
    Registro reg = *(Registro*)a;
    tClave clave=*(tClave*)b;
    if(reg.dni!=clave.dni)
        return reg.dni!=clave.dni;
    return strcmpi(reg.patente,clave.patente);
 }
