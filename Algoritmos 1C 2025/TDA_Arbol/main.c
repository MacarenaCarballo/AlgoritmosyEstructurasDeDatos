#include "head.h"

int main()
{
    tArbol arbol;
    int vec[]={100,50,200,300,20,75,60};
    int clave=100;
    crearArbol(&arbol);

    for(int i=0;i<sizeof(vec)/sizeof(int);i++)
        insertarArbolR(&arbol,&vec[i],sizeof(int),compararEnteros,NULL);

    printf("MOSTAR EN ORDEN\n");
    recorrerInorden(&arbol,imprimirEnteros,NULL);
    printf("MOSTAR EN POSTORDEN\n");
    recorrerPostorden(&arbol,imprimirEnteros,NULL);
    printf("MOSTAR EN PREORDEN\n");
    recorrerPreorden(&arbol,imprimirEnteros,NULL);

    printf("Cantidad de nodos: %d\n",contarNodos(&arbol));
    printf("Cantidad de hojas: %d\n",contarHojas(&arbol));
    printf("Cantidad de no hojas: %d\n",contarNohoja(&arbol));
    printf("Altura Arbol: %d\n",alturaArbol(&arbol));
    printf("Cantidad de nodos con hijo izq: %d\n",contarNodosConIzq(&arbol));
    printf("Cantidad de nodos por nivel: %d\n",cantNodosNivel(&arbol,5));
    printf("Cantidad de nodos hasta nivel: %d\n",cantNodosHastaNivel(&arbol,3));
    printf("Cantidad de nodos desde nivel: %d\n",cantNodosDesdeNivel(&arbol,0));
    if(buscarClave(&arbol,compararEnteros,&clave))
        printf("CLAVE ENCONTRADA\n");
    else
        printf("CLAVE NO ENCONTRADA\n");

    printf("Cantidad de nodos del subarbol derecho para la clave %d es: %d\n",clave,cantNodosPorClaveDer(&arbol,compararEnteros,&clave));
//
//    if(eliminarHoja(&arbol,compararEnteros,&clave))
//        printf("HOJA ELIMINADA\n");
//    else
//        printf("CLAVE NO ENCONTRADA O NO ERA HOJA\n");
   // eliminarTodasHoja(&arbol);
   eliminarDelArbol(&arbol,&clave,sizeof(int),compararEnteros);
    printf("MOSTAR EN ORDEN\n");
    recorrerInorden(&arbol,imprimirEnteros,NULL);


    vaciarArbol(&arbol);
    return 0;
}
