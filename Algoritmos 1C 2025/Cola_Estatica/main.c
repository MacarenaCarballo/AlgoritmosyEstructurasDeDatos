#include "headColaEst.h"

int main()
{
    tCola cola;
    int i, num,num2=4;
    int vec[]={1,2,3};
    crearCola(&cola);

    if(colaVacia(&cola)==COLA_VACIA)
        printf("La cola esta vacia\n");

    if(colaLlena(&cola,10)==COLA_LLENA)
        printf("Cola llena\n");

    for(i=0;i<sizeof(vec)/sizeof(vec[0]);i++)
    {
        ponerEnCola(&cola,&vec[i],sizeof(vec[0]));
    }

    sacarDeCola(&cola,&num,sizeof(int));
    printf("El numero es %d\n",num);
    sacarDeCola(&cola,&num,sizeof(int));
    printf("El numero es %d\n",num);
    ponerEnCola(&cola,&num2,sizeof(int));
    sacarDeCola(&cola,&num,sizeof(int));
    printf("El numero es %d\n",num);
    verPrimero(&cola,&num,sizeof(int));
    printf("El numero es %d\n",num);
    ponerEnCola(&cola,&vec[0],sizeof(vec[0]));
    verPrimero(&cola,&num,sizeof(int));
    printf("El numero es %d\n",num);
    ponerEnCola(&cola,&vec[0],sizeof(vec[0]));

//    cargarArchivoPrueba("entrada.txt");
//    bajarArchivo("entrada.txt", &cola);
//    printf("El archivo de entrada se ha procesado correctamente\n");
    return 0;
}
