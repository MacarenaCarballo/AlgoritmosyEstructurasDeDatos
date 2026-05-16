#include "funciones.h"
int main()
{
    tPila pila;
    char nombre[]="maca";
    char dato[TAM];
    printf("Longitud del dato es: %d\n",mi_Strlen(nombre));
    crearPila(&pila);
    apilar(&pila,(void*)nombre,mi_Strlen(nombre)+1);
    verTope(&pila,(void*)dato,TAM);
    printf("%s",dato);
    return 0;
}
