#include "colaDinamica.h"

int main()
{
    tCola cola;
    float num1,num=2.5;
    crearCola(&cola);

    if(colaVacia(&cola)==COLA_VACIA)
        printf("Cola Vacia\n");

    ponerEnCola(&cola,&num,sizeof(float));

    verPrimero(&cola,&num1,sizeof(float));
    printf("%f\n",num1);

    if(colaVacia(&cola)==COLA_VACIA)
        printf("Cola Vacia\n");

    sacarDeCola(&cola,&num1,sizeof(float));
    printf("%f\n",num1);

    vaciarCola(&cola);

    return 0;
}
