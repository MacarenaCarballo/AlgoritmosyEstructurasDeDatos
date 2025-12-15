#include "headFinal.h"

int main()
{
    tArbol pa;
    int opcion,num;
    crearArbol(&pa);
    do
    {
        printf("Elija una opcion para empezar\n");
        printf("1-Cargar valores\n");
        printf("2-Mostrar valores en orden ascendente\n");
        printf("3-Mostrar segundo valor minimo\n");
        printf("4-Salir\n");
        do
        {
            scanf("%d",&opcion);
        }while(opcion<1 || opcion>4);
        switch(opcion)
        {
        case 1:
            {
                printf("Ingrese los valores (enteros)- Ingrese 0 para terminar la carga\n");
                do
                {
                    scanf("%d",&num);
                    if(num!=0)
                        if(insertarEnOrden(&pa,&num,sizeof(int),compararEnteros)!=HECHO)
                            break;
                }while(num!=0);
            }
            break;
        case 2:
            {
                printf("Arbol de forma ascendente\n");
                recorrerPreOrden(&pa,mostrarEntero,NULL);
            }
            break;
        case 3:
            {
                //menorBuscar(&pa,mostrarEntero);
                buscarSegundoMenor(&pa,compararEnteros);
                //printf("El segundo menor es %d\n",menor);
            }
            break;
        case 4:
            printf("Saliendo...\n");
        }

    }while(opcion!=4);
    vaciarArbol(&pa);
    return 0;
}
