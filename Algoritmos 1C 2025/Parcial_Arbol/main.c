#include "parcialArbol.h"
int main()
{
    tArbol pA,pB;
    crearArbol(&pA);
    crearArbol(&pB);
    printf("ARCHIVO A\n");
    procesarArchivos("A.txt",&pA,compararStrings);
    recorrerInOrden(&pA,mostrarString,NULL);
    printf("ARCHIVO B\n");
    procesarArchivos("B.txt",&pB,compararStrings);
    recorrerInOrden(&pB,mostrarString,NULL);

    FILE *pf=fopen("AmenosB.txt","at");
    if(!pf)
        return ERRORCOD;

    aMENOSb(&pA,&pB);
    recorrerInOrden(&pA,archivoString,pf);


    vaciarArbol(&pA);
    vaciarArbol(&pB);
    return 0;
}
