#include "head.h"

int main()
{
    int dni;
    char opcion, ordenamiento;
    tLista  lista;
    crearLista(&lista);
    //crearLote("ImpuestosVencidos.dat");
    leerArchivo("ImpuestosVencidos.dat",&lista);
    mostrarListaPrincipio(&lista,mostrarReg);

    do
    {
        puts("Bienvenido..\n");
        puts("1- PARA VER DEUDAS.\n");
        puts("2- PARA SALIR.\n");
        scanf(" %c",&opcion);
        getchar();

        if(opcion=='1')
        {
            do
            {
                puts("Ingrese nro dni\n");
                scanf("%d",&dni);
            }
            while(dni<1000000 || dni>99999999);

            do
            {
                puts("Ingrese Metodo de ordenamiento para su ARCHIVO DE DEUDAS\n");
                puts("A- DNI\nB- DNI y PATENTE\n");
                scanf(" %c",&ordenamiento);
                ordenamiento=toupper(ordenamiento);

            }
            while(ordenamiento!='A' && ordenamiento!='B');
            FILE *pf=fopen("deuda.txt","at");
            if(!pf)
                return ERRORCOD;

            tLista pFiltrada;
            crearLista(&pFiltrada);
            if(ordenamiento=='A')
            {

                filter(&lista,compararDniEspecifico,crearDeuda,&dni,&pFiltrada);
                if(pFiltrada!=NULL)
                {
                    float deuda=deudaTotal(&pFiltrada);
                    cargarArchivoDNI(&pFiltrada,pf,deuda);
                    printf("Archivo Cargado!\n");
                }
                else
                {
                    printf("No tiene deudas pendientes\n");
                }


            }
            else
            {
                char patente[8];
                tClave clave;
                clave.dni=dni;
                puts("Ingrese nro Patente");
                scanf("%s", patente);
                strcpy(clave.patente,patente);
                filter(&lista,compararDniyPatenteEspecifico,crearDeuda,&clave,&pFiltrada);
                if(pFiltrada!=NULL)
                {
                    float deuda=deudaTotal(&pFiltrada);
                    cargarArchivoDNIyPatente(&pFiltrada,pf,deuda);
                    printf("Archivo Cargado!\n");
                }
                else
                {
                    printf("No tiene deudas pendientes\n");
                }

            }
            fclose(pf);
            vaciarLista(&pFiltrada);
        }
    }
    while(opcion!='2');
    vaciarLista(&lista);
    return 0;
}
