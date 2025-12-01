#include "headPila.h"

int main()
{
    tPila p;
    char vec[]={'a','b','c','d'};
    char vista;
    crearPila(&p);
    apilar(&p,&vec[0],sizeof(char));
    apilar(&p,&vec[1],sizeof(char));
    verTope(&p,&vista,sizeof(char));
    printf("%c\n",vista);
    apilar(&p,&vec[2],sizeof(char));
    desapilar(&p,&vista,sizeof(char));
    printf("%c\n",vista);
    desapilar(&p,&vista,sizeof(char));
    printf("%c\n",vista);
    desapilar(&p,&vista,sizeof(char));
    printf("%c\n",vista);
    vaciarPila(&p);
    return 0;
}
