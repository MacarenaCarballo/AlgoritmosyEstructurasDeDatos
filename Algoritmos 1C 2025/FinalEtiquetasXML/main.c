#include "headerFinal.h"

int main()
{
    char nombre[]="dato.xml";
    char version[5];
    printf("Ingrese la version en formato XXYY\n");
    fgets(version,5,stdin);

    if(validarXMLExtenso(nombre,version)==0)
        printf("Se valida correctamente el archivo XML\n");
    else
        printf("Archivo XML mal estructurado\n");
    return 0;
}
