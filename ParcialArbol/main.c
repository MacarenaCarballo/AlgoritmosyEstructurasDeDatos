#include "headArbol.h"

int main()
{
    tArbol pa;
    int ocurrencia=3;
    crearArbol(&pa);
    bajarArchivo("datos.txt",&pa);
    recorrerInOrden(&pa,mostrar);
    printf("Hay %d ocurrencias.\n",contarocurrencias(&pa,&ocurrencia,compararNoclave));
    espejarArbol(&pa);
    recorrerInOrden(&pa,mostrar);
    vaciarArbol(&pa);
    return 0;
}
