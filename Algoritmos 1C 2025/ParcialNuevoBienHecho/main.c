#include "header.h"

//USE LISTA SIMPLE YA QUE NECESITO RECORRELA PARA INSERTAR ORDENADO
int main()
{
    char opcion;
    int porcentaje, xPedido=0, archProcesado=0;
    char nomA[30], nomO[30];

    // crearLotePrueba("Entrada.bin");

    do
    {
        mostrarMenu();
        do
        {
            scanf(" %c",&opcion);
            if(opcion!='2' && opcion!='1' && opcion!='3' && opcion!='4' && opcion!='5')
                puts("Intente nuevamente\n");
        }
        while(opcion!='2' && opcion!='1' && opcion!='3' && opcion!='4' && opcion!='5');

        switch(opcion)
        {
        case '3':
        {
            puts("MOSTRANDO ARCHIVO DE ENTRADA.bin...\n");
            leerLote("Entrada.bin");
        }
        break;
        case '5':
            puts("SALIENDO DEL PROGRAMA, GRACIAS!\n");
            break;

        case '1':
        {
            do
            {
                puts("Ingrese un valor X para marcar l porcentaje de aprobacion\n");
                scanf("%d", &porcentaje);
            }
            while(porcentaje<=0);
            xPedido=1;
        }
        break;
        case '2':
        {
            if(xPedido)
            {
                puts("PROCESANDO ARCHIVOS..\n");
                sprintf(nomA,"LotesAprobados-%d.txt",porcentaje);
                sprintf(nomO,"LotesObservados-%d.txt",porcentaje);
                procesarArchivos(nomA,nomO,porcentaje,"Entrada.bin");
                archProcesado=1;
            }
            else
                puts("Primero ingrese el porcentaje\n");

        }
        break;
        case '4':
        {
            if(archProcesado)
            {
                mostrarArchivos("APROBADOS",nomA,porcentaje);
                mostrarArchivos("OBSERVADOS",nomO,porcentaje);
            }
            else
            {
                printf("Primero Procese los archivos\n");
            }
        }
        }
        system("pause");
        system("cls");
    }
    while(opcion!='5');

    return 0;
}
