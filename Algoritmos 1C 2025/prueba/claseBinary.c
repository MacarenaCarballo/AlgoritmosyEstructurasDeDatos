#include <stdio.h>
int main()
{
    FILE *pf=fopen("Modo de apertura", "Nombre del archivo.dat");

    if(pf==NULL)
        puts("ERROR DE APERTURA!");
}
