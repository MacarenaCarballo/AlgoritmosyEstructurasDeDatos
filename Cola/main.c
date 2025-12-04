#include "headCola.h"

int main()
{
    tCola pc;
    crearCola(&pc);
    char vec[]={'a','b','c','d'};
    char vista;
    ponerEnCola(&pc,&vec[0],sizeof(char));
    ponerEnCola(&pc,&vec[1],sizeof(char));
    ponerEnCola(&pc,&vec[2],sizeof(char));
    verPrimero(&pc,&vista,sizeof(char));
    printf("%c\n",vista);
    sacarDeCola(&pc,&vista,sizeof(char));
    printf("%c\n",vista);
    verPrimero(&pc,&vista,sizeof(char));
    printf("%c\n",vista);
    vaciarCola(&pc);
    return 0;
}
