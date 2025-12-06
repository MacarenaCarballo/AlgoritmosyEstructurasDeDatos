#include "headDoble.h"

int main()
{
    tLista pl;
    crearLista(&pl);
    char vecChar[8]={'a','h','c','y','e','m','m','m'};
    char clave;
    for(int i=0;i<8;i++)
        insertarOrdenado(&pl,&vecChar[i],sizeof(char),compararCaracteres);
    mapeo(&pl,mostrarLista);
    printf("SACO LISTA\n");
    clave='h';
    //eliminarNodo(&pl,&clave,sizeof(char),compararCaracteres);
    filter(&pl,siEs,&clave);
    mapeo(&pl,mostrarLista);
    vaciarLista(&pl);
    return 0;
}
