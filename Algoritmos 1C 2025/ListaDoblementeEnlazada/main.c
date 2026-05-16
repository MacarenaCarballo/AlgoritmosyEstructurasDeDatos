#include "listaDoble.h"

int main()
{
    int vec[]={1,2,6,8,3,7,9};
    //int elim=7;
    unsigned n;
    tLista lista;
    crearLista(&lista);

    n=sizeof(vec)/sizeof(int);
    for(int i=0;i<n;i++)
    {
        insertarNodo(&lista,&vec[i],sizeof(unsigned),compararEnteros,NULL, NULL);
    }
    printf("MUESTRA DESDE EL FINAL\n");
    mostrarListaFinal(&lista,mostrarEntero);
    printf("\nMUESTRA DESDE EL PRINCIPIO\n");
    mostrarListaPrincipio(&lista,mostrarEntero);
    printf("FILTER PARES\n");
    filter(&lista,borrarPares,NULL);
    mostrarListaPrincipio(&lista,mostrarEntero);

//    printf("\nELIMINO NODO: %d\n",elim);
//    if(eliminarNodo(&lista,&elim,sizeof(int),compararEnteros)!=NO_ENCONTRADO)
//        mostrarListaPrincipio(&lista,mostrarEntero);
//    else
//        printf("Nodo no encontrado intente nuevamente\n");

    vaciarLista(&lista);
    return 0;
}
