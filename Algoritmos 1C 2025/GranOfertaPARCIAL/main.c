#include "parcial.h"

int main()
{
    char opcion;
    tLista stock;
    crearLista(&stock);
    int archivoGenerado=0,fecha=0;
    t_Fecha act;

    do
    {
        puts("BIENVENIDO A LA GRAN OFERTA\n");
        puts("***********************************************");
        puts("1- GENERAR LOTE DE PRUEBA\n");
        puts("2- INGRESAR FECHA ACTUAL\n");
        puts("3- MOSTRAR LOS N PRODUCTOS A VENCER\n");
        puts("4- GENERAR ARCHIVO DE LOS PRODUCTOS A VENCER\n");
        puts("5- MOSTRAR EL PRODUCTO MAS PROXIMO A VENCER\n");
        puts("6- SALIR\n");

        puts("***********************************************");
        do
        {
            puts("Ingrese una opcion del 1-6\n");
            scanf("%c",&opcion);
            getchar();
            if(opcion<'1' || opcion>'6')
            {
                puts("Ingrese una opcion valida para continuar\n");
            }
        }
        while(opcion<'1' || opcion>'6');
        switch(opcion)
        {
        case '1':
        {
            printf("Generando lote de prueba....\n");
            generarLote("Stock.dat");
            //leerLote("Stock.dat");
            bajarArchivo("Stock.dat",compararFechas,&stock,mostrarStock);
            archivoGenerado=1;
        }
        break;
        case '2':
        {
            obtenerFecha(&act);
            puts("LA FECHA ACTUAL ES:");
            printf("%d/%d/%d\n",act.dia,act.mes,act.anio);
            fecha=1;
        }
        break;
        case '3':
        {
            if(archivoGenerado && fecha)
                productosAVencer(&stock,mostrarStock,act);
            else
                printf("PRIMERO GENERE EL ARCHIVO Y LA FECHA\n");
        }
        break;
        case '4':
        {
            if(archivoGenerado && fecha)
            {
                puts("Generando archivo..\n");
                productosAVencer(&stock,generarStock,act);
            }
            else
                printf("PRIMERO GENERE EL ARCHIVO Y LA FECHA\n");
        }
        break;
        case '5':
        {
            if(archivoGenerado && fecha)
            {
                puts("EL MAS PROXIMO A VENCER ES:\n");
                mostrarMasproximo(&stock);
            }
            else
                printf("PRIMERO GENERE EL ARCHIVO Y LA FECHA\n");
        }
        break;
        case '6':
            puts("Saliendo del programa..\n");
            break;

        default:
            puts("Opcion erronea Intente nuevamente\n");
        }


        system("pause");
        system("cls");
        getchar();
    }
    while(opcion!='6');
    vaciarLista(&stock);

    return 0;
}
