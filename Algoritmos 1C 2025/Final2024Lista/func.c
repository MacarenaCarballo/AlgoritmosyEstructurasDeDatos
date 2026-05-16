#include "head.h"
int crearLote(char *lote)
{
    FILE *pf=fopen(lote,"wt");
    if(!pf)
        return 1;
    tMateria materias_ejemplo[] =
    {
        {1001, "20241A", 8},
        {1002, "20241B", 6},
        {1003, "20232B", 9},
        {2001, "20231A", 7},
        {2002, "20231B", 8},
        {2003, "20231C", 9},
        {3001, "20222A", 6},
        {3002, "20222B", 5},
        {4001, "20241A", 10},
        {5001, "20241B", 7}
    };

    tAlumno alumno[]= {{12345678, "Gomez", "Laura", "INF", materias_ejemplo[0]},
        {87654321, "Martinez", "Carlos", "ELE", materias_ejemplo[1]},
        {11223344, "Fernandez", "Ana", "IND", materias_ejemplo[2]},
        {33445566, "Fernandez", "Julia", "ABO", materias_ejemplo[3]}
    };

    for(int i = 0; i < 4; i++)
    {
        fprintf(pf, "%u|%s|%s|%s|%u|%s|%u\n",
                alumno[i].dni,
                alumno[i].apellido,
                alumno[i].nombre,
                alumno[i].codCarrera,
                alumno[i].materia.codMat,
                alumno[i].materia.codCursada,
                alumno[i].materia.notaFinal);
    }
    fclose(pf);
    return 0;
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
void trozado(char *linea, tAlumno *info)
{
    char *act;

    act = strrchr(linea, '\n');
    if (act) *act = '\0';

    act = strrchr(linea, '|');
    info->materia.notaFinal = (unsigned)atoi(act + 1);
    *act = '\0';

    act = strrchr(linea, '|');
    strcpy(info->materia.codCursada, act + 1);
    *act = '\0';

    act = strrchr(linea, '|');
    info->materia.codMat = (unsigned)atoi(act + 1);
    *act = '\0';

    act = strrchr(linea, '|');
    strcpy(info->codCarrera,act+1);
    *act = '\0';

    act = strrchr(linea, '|');
    strcpy(info->nombre,act+1);
    *act = '\0';

    act = strrchr(linea, '|');
    strcpy(info->apellido,act+1);
    *act = '\0';

    info->dni=(unsigned)atoi(linea);
}
int insertarAlPrincipio(tLista *pl, void *dato, unsigned tam)
{
    tNodo *nue=malloc(sizeof(tNodo));
    if(!nue)
        return 1;
    nue->dato=malloc(tam);
    if(!nue->dato)
    {
        free(nue);
        return 1;
    }
    memcpy(nue->dato,dato,tam);
    nue->tam=tam;
    nue->sig=*pl;
    *pl=nue;
    return 0;
}

int cargarAlista(tLista *pl, char *nombre)
{
    char linea[100];
    FILE *pf=fopen(nombre,"rt");
    if(!pf)
        return 1;
    tAlumno reg;
    while(fgets(linea,100,pf))
    {
        trozado(linea,&reg);
        insertarAlPrincipio(pl,&reg,sizeof(tAlumno));
    }
    fclose(pf);
    return 0;
}

void mapeo(tLista *pl,tAccion accion)
{
    if(!*pl)
        return;
    while(*pl)
    {
        accion((*pl)->dato,NULL);
        pl=&(*pl)->sig;
    }
}

void mostrarLista(void *a, void *b)
{
    tAlumno alumno=*(tAlumno*)a;
    printf("%u|%s|%s|%s|%u|%s|%u\n",
           alumno.dni,
           alumno.apellido,
           alumno.nombre,
           alumno.codCarrera,
           alumno.materia.codMat,
           alumno.materia.codCursada,
           alumno.materia.notaFinal);
}

void mostrarAlreves(tLista *pl, tAccion accion)
{
    if(!*pl)
        return;
    mostrarAlreves(&(*pl)->sig,accion);
    accion((*pl)->dato,NULL);
}

tLista *buscarMenor(tLista *pl, tCmp comparar)
{
    tLista *menor=pl;
    tLista *act=&(*pl)->sig;
    while(*act)
    {
        if(comparar((*act)->dato,(*menor)->dato)<0)
            menor=act;
        act=&(*act)->sig;
    }
    return menor;
}

int ordenamientoSeleccion(tLista *pl, tCmp comparar)
{
    tLista *ant=pl;
    tLista *menor;
    tNodo *aux;
    while(*ant)
    {
        menor=buscarMenor(ant,comparar);
        if(menor!=ant)
        {
            aux=*menor;
            *menor=aux->sig;
            aux->sig=*ant;
            *ant=aux;
        }
        ant=&(*ant)->sig;
    }
    return 0;
}

int compararDNI(void *a, void *b)
{
    tAlumno reg1=*(tAlumno*)a;
    tAlumno reg2=*(tAlumno*)b;
    return (int)reg1.dni-reg2.dni;
}

int compararApeNomDni(void *a, void *b)
{
    tAlumno reg1=*(tAlumno*)a;
    tAlumno reg2=*(tAlumno*)b;
    if(strcmp(reg1.apellido,reg2.apellido)!=0)
        return strcmp(reg1.apellido,reg2.apellido);
    if(strcmp(reg1.nombre,reg2.nombre)!=0)
        return strcmp(reg1.nombre,reg2.nombre);
    return (int)reg1.dni-reg2.dni;
}
