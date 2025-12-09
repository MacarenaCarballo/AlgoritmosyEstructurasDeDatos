#include "headers.h"

int main()
{
    t_tabla_puntos tabla;
//    t_puntaje vec[]={{"AAA",20},
//    {"ABA",10},
//    {"ACA",80}};
//    crear_tabla_puntos(&tabla,2);
//    for(int i=0; i<3; i++)
//    {
//        agregar_puntaje(&tabla,&vec[i]);
//    }
    tablaPuntaje("Puntaje.txt",&tabla);
   // imprimir_tabla_puntos(&tabla);
    vaciar_tabla_puntos(&tabla);
    return 0;
}
