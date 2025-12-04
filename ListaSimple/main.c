#include "headLista.h"

int main()
{
    tLista pl;
    crearLista(&pl);
    char vecChar[8]={'a','h','c','y','e','m','m','m'};
    char clave;
    for(int i=0;i<8;i++)
        insertarOrdenado(&pl,&vecChar[i],sizeof(char),compararCaracteres);

    mapeo(&pl,mostrarLista);
    clave='m';
    printf("SACO LISTA\n");
    sacarLista(&pl,&clave,sizeof(char),compararCaracteres);
    mapeo(&pl,mostrarLista);
    vaciarLista(&pl);
    return 0;
}
