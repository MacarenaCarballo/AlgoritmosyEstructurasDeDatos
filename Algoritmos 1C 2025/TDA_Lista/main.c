#include "lista_head.h"
#include "pilaDinamica.h"

int main()
{
    tLista lista;//listaChar;
    int i;//numDATO=6;
    int vecInt[]={1,6,3,2,5,8,9,7,-1};
   // char vecChar[]={'a','h','c','y','e','m'};
//    char vecChar[]={'a','b','c','c','c','m'};
//    char letra='c';
    unsigned n2;



//PRUEBAS CON INT(ENTEROS)
    n2=sizeof(vecInt)/sizeof(int);

    crearLista(&lista);

    for(i=0;i<n2;i++)
        ponerAlComienzo(&lista,&vecInt[i],sizeof(int));

    if(listaVacia(&lista))
        printf("La lista esta vacia\n");

    printf("LISTA ORIGINAL\n");
    mostrarLista(&lista, mostrarEntero);

//    mapV2(&lista,multiplicarPor3);
//    printf("\n LOS NUMEROS MULTIPLICADOS POR 3 SON:\n");
//    mostrarLista(&lista, mostrarEntero);
//
//    mapV2(&lista,alCuadrado);
//    printf("\n LOS NUMEROS AL CUADRADO SON:\n");
//    mostrarLista(&lista, mostrarEntero);
//
//    printf("ELIMINO EL 6\n");
//    eliminarNodoDuplicadosDesordenada(&lista,&numDATO,sizeof(int),compararEnteros);
//    mostrarLista(&lista, mostrarEntero);
//
//
    printf("LISTA ORDENADA\n");
    ordenamientoDeNodos(&lista,compararEnteros);
    mostrarLista(&lista, mostrarEntero);


//    printf("Mostar Lista Inversa Recursiva\n");
//    mostrarListaInversa(&lista, mostrarEntero);
//        printf("\nMostar Lista Inversa Iterativa\n");
//        mostrarListaInversaItera(&lista, mostrarEntero,sizeof(int));


//PRUEBAS CON CHAR
//    crearLista(&listaChar);
//
//    if(listaVacia(&lista))
//        printf("La lista esta vacia\n");
//
//    n=sizeof(vecChar)/sizeof(char);
//
//    for(i=0;i<n;i++)
//        ponerAlComienzo(&listaChar,&vecChar[i],sizeof(char));
//
//    mostrarLista(&listaChar, mostrarChar);
//
//    eliminarNodoDuplicadosOrdenada(&listaChar,&letra,sizeof(char),compararLetras);
//    printf("ELIMINO C\n");
//
//    mostrarLista(&listaChar, mostrarChar);


    vaciarLista(&lista);
//   vaciarLista(&listaChar);
    return 0;
}
