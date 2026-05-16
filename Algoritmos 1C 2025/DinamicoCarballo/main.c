#include "func.h"

int main()
{
    tPila pila1;
    int vec[]={1,2,3};
    int num;
    crearPila(&pila1);
    if(pilaVacia(&pila1))
        printf("PILA VACIA\n");
    else
        printf("ashe");
    apilar(&pila1,&vec[0],sizeof(int));
    apilar(&pila1,&vec[1],sizeof(int));
    verTope(&pila1,&num,sizeof(int));
    printf("El num es: %d\n",num);
    desapilar(&pila1,&num,sizeof(int));
    desapilar(&pila1,&num,sizeof(int));
    desapilar(&pila1,&num,sizeof(int));
    printf("El num es: %d\n",num);
    vaciarPila(&pila1);
    return 0;
}
