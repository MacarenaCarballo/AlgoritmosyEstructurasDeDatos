#include "head.h"
int main()
{
    tCola pc;
    Empleado emp;
    crearCola(&pc);
    procesarArchivoTxt("Empleados.txt",&pc);
    desencolar(&pc,&emp,sizeof(Empleado));
    printf("EL CLIENTE ATENDIDO ES:%s\n",emp.nombre);

    vaciarCola(&pc);
    return 0;
}
