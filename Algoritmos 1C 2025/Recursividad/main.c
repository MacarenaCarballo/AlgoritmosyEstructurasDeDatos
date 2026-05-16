#include "recursividad.h"

int main()
{
    int nro=10, suma;

    for(int i=0;i<=nro;i++)
        printf("La suma de %d es: %d\n",i,sumaNaturales(i));

    suma=sumaNaturales(-2);
    if(suma!=-1)
        printf("La suma es: %d\n",suma);
    else
        printf("No es numero natural\n");

    for(int i=-6;i<=nro;i++)
        printf("La suma de %d es: %d\n",i,sumarHastaN(i));


    printf("*\n");
    mostrarCadaLetra("Hola");
    mostrarInvertido("Hola");
    printf("*\n");
    escaleraLetras("Hola",5);
    printf("*\n");

   // mostrarNumero(1234);
    mostrarEscalera2(1234);
    return 0;
}
