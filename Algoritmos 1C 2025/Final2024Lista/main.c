#include "head.h"
int main()
{
    tLista pl;
    crearLista(&pl);
    crearLote("Alumnos.txt");
    cargarAlista(&pl,"Alumnos.txt");
    mapeo(&pl,mostrarLista);

    puts("\nOrden inverso\n");
    mostrarAlreves(&pl,mostrarLista);

    puts("\nORDENADO POR DNI\n");
    ordenamientoSeleccion(&pl,compararDNI);
    mapeo(&pl,mostrarLista);

    puts("\nORDENADO POR APELLIDO, NOMBRE Y DNI\n");
    ordenamientoSeleccion(&pl,compararApeNomDni);
    mapeo(&pl,mostrarLista);


    vaciarLista(&pl);
    return 0;
}
