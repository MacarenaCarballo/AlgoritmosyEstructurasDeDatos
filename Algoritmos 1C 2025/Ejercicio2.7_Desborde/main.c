#include "head_Ejercicio2.7.h"
#include "Ejercicio2.7Hibrido.h"

int main()
{
    char nro1[TAM_CAD];
    char nro2[TAM_CAD];
    tPila pila1,pila2,pilaRes;

    crearPila(&pila1);
    bajarArchivoTxt("nro1.txt",nro1);
    printf("NRO1:");
    if(prepararPila(&pila1,nro1)==-1)
        return 0;
    printf("\n");


    crearPila(&pila2);
    bajarArchivoTxt("nro2.txt",nro2);
    printf("NRO2:");
    if(prepararPila(&pila2,nro2)==-1)
        return 0;

    printf("\n");
    printf("\n");
    crearPila(&pilaRes);
    sumaDosNumerosGrande(&pila1,&pila2,&pilaRes);
    printf("RESULTADO CON PILA ESTATICA:");
    subirArchivoTxt("resultado.txt",&pilaRes);

    vaciarPila(&pila1);
    vaciarPila(&pila2);
    vaciarPila(&pilaRes);


/*SUMA CON IMPLEMENTACION HIBRIDA*/

//    t_Pila pila1,pila2,pilaRes;
//
//    crearPilaH(&pila1);
//    bajarArchivoTxt("nro1.txt",nro1);
//    printf("NRO1:");
//    if(prepararPilaH(&pila1,nro1)==-1)
//        return 0;
//
//    printf("\n");
//
//
//    crearPilaH(&pila2);
//    bajarArchivoTxt("nro2.txt",nro2);
//    printf("NRO2:");
//    if(prepararPilaH(&pila2,nro2)==-1)
//        return 0;
//
//    printf("\n");
//    printf("\n");
//
//    crearPilaH(&pilaRes);
//    sumaDosNumerosGrandeH(&pila1,&pila2,&pilaRes);
//    printf("RESULTADO CON PILA DINAMICA:");
//    subirArchivoTxtH("resultadoDinamico.txt",&pilaRes);
//
//    vaciarPilaH(&pila1);
//    vaciarPilaH(&pila2);
//    vaciarPilaH(&pilaRes);

    return 0;
}
