#include "pila_hibrida.h"

int main()
{
    FILE *pf=fopen("datos.dat","rb");
    if (!pf)
    {
        puts("Error al abrir archivo para lectura");
        return 1;
    }
//    for(int i=0;i<10;i++)
//    {
//        fwrite(&i,sizeof(i),1,pf);
//    }
// fwrite(emp,sizeof(emp),1,ap);
// GRABO EL VECTOR ENTERO (SIZEOF(EMP)) Y LE INDICO QUE SOLO UNA VEZ LO COPIO
    t_Pila pilaH;
    int menu = -1;
    char entrada[10];

    int obtenerDato,dato;


    crearPila(&pilaH);

    do
    {

        printf("///////////////////MENU DE PILA HIBRIDA////////////////////\n");
        printf("1- Apilar\n");
        printf("2- Despilar\n");
        printf("3- Consultar Tope\n");
        printf("4- Consultar si esta Vacia\n");
        printf("5- Consultar si esta Llena\n");
        printf("6- Vaciar Pila\n");
        printf("0- Salir\n");

        printf("Ingrese una opción: ");
        scanf("%s", entrada);

        int esNumero = 1;
        for (int i = 0; entrada[i] != '\0'; i++)
        {
            if (!isdigit(entrada[i]))
            {
                esNumero = 0;
            }
        }

        if (esNumero)
        {
            menu = atoi(entrada);

            switch (menu)
            {
            case 1:
            {
                if (fread(&dato, sizeof(int), 1, pf) == 1)
                {
                    printf("El dato a apilar es: %d\n", dato);
                    int res = apilar(&pilaH, &dato, sizeof(dato));
                    if (res == PILA_LLENA)
                        puts("No se pudo apilar: PILA LLENA\n");
                    else if (res == SIN_MEM)
                        puts("No se pudo apilar: SIN MEMORIA\n");
                    else
                        puts("Dato apilado correctamente.\n");
                }
                else
                {
                    puts("Ya no hay mas datos en el archivo para apilar.\n");
                }

            }
            break;
            case 2:
            {
                int res = desapilar(&pilaH, &obtenerDato, sizeof(int));
                if (res == PILA_VACIA)
                    puts("No se puede desapilar: PILA VACIA\n");
                else
                    printf("El dato desapilado es: %d\n", obtenerDato);


            }
            break;
            case 3:
            {
                int res = verTope(&pilaH, &obtenerDato, sizeof(int));
                if (res == PILA_VACIA)
                    puts("No hay tope: PILA VACIA\n");
                else
                    printf("El tope actual es: %d\n", obtenerDato);

            }
            break;

            case 4:
                if (pilaVacia(&pilaH))
                    puts("La pila esta VACIA.\n");
                else
                    puts("La pila NO esta vacía.\n");
                break;

            case 5:
                if (pilaLlena(&pilaH))
                    puts("La pila esta LLENA.\n");
                else
                    puts("La pila NO esta llena.\n");
                break;

            case 6:
                vaciarPila(&pilaH);
                puts("La pila ha sido vaciada.\n");
                break;
            case 0:
                puts("Saliendo del caso de prueba...");
                break;

            default:
                puts("Opcion Invalida.\n");

            }
        }else
            printf("Entrada no válida. Por favor ingrese un número.\n");

            system("pause");
            system("cls");

        }
        while(menu!=0);


        fclose(pf);
        vaciarPila(&pilaH);


        return 0;
    }

