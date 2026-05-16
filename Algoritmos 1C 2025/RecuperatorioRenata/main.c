#include "headRecuperatorio.h"
int main()
{
    char opcion;
    int cargue=0;
    int valor;
    tArbol pa;
    crearArbol(&pa);
    crearLote("Datos.csv");
    do
    {
        printf("*************Menu Arbol****************\n");
        printf("a- Cargar Arbol\n");
        printf("b- Mostrar Arbol\n");
        printf("c- Contar ocurrencias en dato NO clave\n");
        printf("d- Espejar Arbol\n");
        printf("e- Salir\n");

        do
        {
            printf("Inserte una opcion\n");
            scanf(" %c",&opcion);
        }
        while(opcion!='a' && opcion!='b' && opcion!='c' && opcion!='d' && opcion!='e');

        switch(opcion)
        {
        case 'a':
        {
            cargarArbol(&pa,"Datos.csv");
            cargue=1;
        }
        break;
        case 'b':
        {
            if(cargue==1)
                recorrerInOrden(&pa,mostrarArbol);
            else
                printf("El arbol no esta cargado\n");
        }
        break;
        case 'c':
        {
            if(cargue==1)
            {
                printf("Ingrese el dato a buscar\n");
                scanf("%d",&valor);
                printf("La cantidad de veces que aparece el dato %d es de %d\n",valor,contarOcurrencias(&pa,compararDato,&valor));
            }
            else
                printf("El arbol no esta cargado\n");
        }
        break;
        case 'd':
        {
            if(cargue==1)
                espejarArbol(&pa);
            else
                printf("El arbol no esta cargado\n");
        }
        break;
        case 'e':
            printf("Saliendo del programa....\n");
            break;
        }
        system("pause");
        system("cls");
    }
    while(opcion!='e');
    vaciarArbol(&pa);
    return 0;
}
