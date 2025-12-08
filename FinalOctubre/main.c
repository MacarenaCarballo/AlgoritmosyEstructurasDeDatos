#include "final.h"

int main()
{
    tLista p1, p2;
    printf("Polinomio 1\n");
    bajarPolinomio("P1.txt",&p1);
    mapeo(&p1,mostrarLista);
    printf("Polinomio 2\n");
    bajarPolinomio("P2.txt",&p2);
    mapeo(&p2,mostrarLista);
    sumarPolinomios(&p1,&p2,compararPotencia,sumarCoeficientes);
    vaciarLista(&p1);
    vaciarLista(&p2);
    return 0;
}
