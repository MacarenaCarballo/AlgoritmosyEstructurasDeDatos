#include "headAlgoritmos.h"

int main()
{
    tArbol pa,pi;
    crearArbol(&pa);
    crearArbol(&pi);
    //generarLote("Stock.dat");
    leerLote("Stock.dat",&pa,compararNada);
    recorrerInOrden(&pa,mostrarCodProd);
    recorrerInOrden(&pa,crearIndice);
    leerIndice("Indice.idx");
    FILE *pf=fopen("Indice.idx","rb");
    if(!pf)
        return ERRORCOD;
    int ini=0,fin;
    fseek(pf,0,SEEK_END);
    fin=ftell(pf)/sizeof(tIndice);
    printf("%d\n",fin);
    balancear(pf,ini,fin,&pi);
    fclose(pf);
    printf("Arbol balanceado\n");
    recorrerInOrden(&pi,mostrarCodProd);
    vaciarArbol(&pa);
    vaciarArbol(&pi);

    return 0;
}
