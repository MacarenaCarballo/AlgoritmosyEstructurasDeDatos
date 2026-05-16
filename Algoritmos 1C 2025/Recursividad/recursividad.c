#include "recursividad.h"

int factRec(int n)
{
    if(n==0)
        return 1;
    return n*factRec(n-1);
}

int sumaNaturales(int n)
{
    if(n<0)
        return -1;
    if(n==0)
        return 0;
    return n+sumaNaturales(n-1);
}

int sumarHastaN(int n)
{
    if(n==0)
        return 0;

    if(n<0)
        return n+sumaNaturales(n+1);

    return n+sumaNaturales(n-1);
}

void mostrarCadaLetra(char* cad)
{
    if(!*cad)
        return;
    printf("%c\n",*cad);
    mostrarCadaLetra(cad+sizeof(char));
}

void mostrarInvertido(char* cad)
{
    if(!*cad)
        return;
    mostrarCadaLetra(cad+sizeof(char));
    printf("%c\n",*cad);
}

void escalera(char *cad, int cant)
{
    if(cant<=0)
        return;
    printf("%.*s\n",cant,cad);
    escalera(cad,cant-1);
    printf("%.*s\n",cant,cad);
}

void escaleraLetras(char *cad,int cant)
{
    if(cant<=0)
        return;
    escaleraLetras(cad+1,cant-1);
    printf("%.*s\n",cant,cad);
}

int mostrarNumero(int n)
{
    if(n==0)
        return 0;
    printf("%d\n",n%10);
    return mostrarNumero(n/10);
}

int mostrarEscalera(int n)
{
    if(n==0)
        return 0;
    printf("%d\n",n);
    return mostrarEscalera(n/10);
}

int mostrarEscalera2(int n)
{
    if(n==0)
        return 0;
    printf("%d\n",n);
    mostrarEscalera2(n/10);
    printf("%d\n",n);
    return 0;
}



void mostrarSecuenciaNumero(int numero,int factor)
{
    if(factor > numero)
    {
        printf("%d\n",numero%factor);
        return;
    }
    printf("%d\n",numero%factor);
    mostrarSecuenciaNumero(numero,factor * 10);
}

void mostrarSecuenciaNumeroInverso(int numero,int factor)
{
    if(factor > numero)
    {
        printf("%d\n",numero%factor);
        return;
    }
    mostrarSecuenciaNumeroInverso(numero,factor * 10);
    printf("%d\n",numero%factor);

}

