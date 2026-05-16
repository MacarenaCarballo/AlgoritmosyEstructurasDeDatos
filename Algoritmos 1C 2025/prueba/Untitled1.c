#include <stdio.h>

int main() {
    FILE *fp = fopen("datos.csv", "w");
    if (!fp) {
        perror("Error al crear archivo");
        return 1;
    }

    // Encabezados
    fprintf(fp, "Nombre,Edad,Promedio\n");

    // Filas
    fprintf(fp, "Ana,20,8.5\n");
    fprintf(fp, "Luis,22,7.9\n");
    fprintf(fp, "Paula,19,9.1\n");

    fclose(fp);
    printf("Archivo CSV creado con éxito.\n");
    return 0;
}

