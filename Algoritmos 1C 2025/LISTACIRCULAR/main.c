#include "lista_head.h"

int main()
{

    tLista lista;
    int i,numDATO;
    int vecInt[]={1,6,3,2,5,8,9,7,-1};
    unsigned n2;



//PRUEBAS CON INT(ENTEROS)
    n2=sizeof(vecInt)/sizeof(int);

    crearLista(&lista);

    for(i=0;i<n2;i++)
       agregarNodo(&lista,&vecInt[i],sizeof(int));

    if(listaVacia(&lista))
        printf("La lista esta vacia\n");

    mapLista(&lista,mostrarEntero);

    printf("ELIMINO NODOS\n");
    eliminarNodo(&lista,&numDATO,sizeof(int));
    printf("El numero es: %d\n",numDATO);
    eliminarNodo(&lista,&numDATO,sizeof(int));
    printf("El numero es: %d\n",numDATO);


    vaciarLista(&lista);
    return 0;
}
