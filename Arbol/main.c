#include "headArbol.h"

int main()
{
    tArbol pa;
    crearArbol(&pa);
    char vecChar[6]= {'f','h','c','y','e','m'};
    char clave='h';
    for(int i=0; i<6; i++)
        insertarOrdenado(&pa,&vecChar[i],sizeof(char),compararCaracteres);
    recorrerPreorden(&pa,mostrarLista);
    printf("Cantidad de nodos %d\n",contarNodos(&pa));
    printf("Altura %d\n",alturaArbol(&pa));
    eliminarNodo(&pa,&clave,sizeof(char),compararCaracteres);
    recorrerPreorden(&pa,mostrarLista);
    vaciarArbol(&pa);
    return 0;
}
