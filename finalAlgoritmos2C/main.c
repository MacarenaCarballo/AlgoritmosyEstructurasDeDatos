#include "headers.h"

int main()
{
    t_tabla_puntos tabla;
    tablaPuntaje("Puntajes.txt",&tabla);
    imprimir_tabla_puntos(&tabla);
    vaciar_tabla_puntos(&tabla);
    return 0;
}
