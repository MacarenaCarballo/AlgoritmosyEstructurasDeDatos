#include "controlCalidad.h"

int main()
{
    //cargarArchivoPrueba("entrada.txt");
    tCola cola;
    crearCola(&cola);
    bajarArchivo("entrada.txt", &cola);
    char option;
    do
    {
        puts("\t \t MENU \n"
             "a) Procesar archivo de entrada: \n"
             "b) Mostrar archivo de entrada: \n"
             "c) Mostrar Archivo de salida \n"
             "f) Salir \n\n"
             "Elija su opcion: ");

        puts("Ingrese una opcion: "); // Reemplazar caracteres especiales
        scanf(" %c", &option);
        option=tolower(option);
        fflush(stdin);

        switch(option)
        {

        case 'a':
            tCola colaCopia;
            crearCola(&colaCopia);
            colaCopia=cola;
            procesarEntrada(&colaCopia);
            puts("\nArchivo Procesado!\n");
            break;

        case 'b':
            puts("\nMostrar Archivo Entrada\n");
            break;

        case 'c':
            puts("\nMostrar Archivo de salida\n");
            break;

        case 'f':
            puts("\nSaliendo");
            break;
        default:
            printf("\nOpcion invalida. Intente de nuevo.\n"); // Reemplazar caracteres especiales
        }

        system("pause");
        system("cls");

    }
    while(option != 'f');

    return 0;
}
