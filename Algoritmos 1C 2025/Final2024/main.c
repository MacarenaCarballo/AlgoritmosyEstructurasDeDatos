#include "finalhead.h"
int main()
{
    tArbol pa;
    char opcion;
    int nivel,cant;
    crearArbol(&pa);
    //crearLote("datos.txt");
    do{
        do{
            printf("Introduzca una opcion(1-4)\n");
            scanf(" %c",&opcion);
        }while(opcion!='1' && opcion!='2' && opcion!='3' && opcion!='4');
        switch(opcion)
        {
            case '1':{
                bajarArchivo("datos.txt",&pa);
                preOrden(&pa,mostrarArbol,NULL);
            }
            break;
            case '2':{
                do{
                    printf("Ingrese un nivel para contar los nodos\n");
                    scanf("%d",&nivel);
                }while(nivel<0);
              printf("Cant de nodos: %d\n", contarCantNodosPorNivel(&pa,nivel));
            }
            break;
            case '3':{
                do{
                    printf("Ingrese un nivel para contar los nodos\n");
                    scanf("%d",&nivel);
                }while(nivel<0);
                if((cant=esCompleto(&pa, nivel))==0)
                    printf("Es completo\n");
                else if(cant==-1)
                    printf("El nivel no existe\n");
                else
                    printf("Faltan %d nodos para que sea compelto el nivel\n",cant);
            }
            break;
            case '4':{
                printf("Saliendo...\n");
            }
            break;
        }
    }while(opcion!='4');
    return 0;
}
