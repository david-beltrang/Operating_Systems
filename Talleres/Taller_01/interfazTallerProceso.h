#ifndef INTERFAZ_TALLER_PROCESO_H
#define INTERFAZ_TALLER_PROCESO_H

#include <stdio.h>
#include <stdlib.h>

/* Función para leer los valores desde un archivo y almacenarlos en un arreglo */
void leerArchivo(const char *nombreArchivo, int *arreglo, int n) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(archivo, "%d", &arreglo[i]) != 1) {
            fprintf(stderr, "Error al leer el elemento %d del archivo %s\n", i, nombreArchivo);
            fclose(archivo);
            exit(EXIT_FAILURE);
        }
    }

    fclose(archivo);
}

/* Función para sumar los valores contenidos en un arreglo */
int sumarArreglo(int *arreglo, int tamano) {
    int suma = 0;

    for (int i = 0; i < tamano; i++) {
        suma += arreglo[i];
    }
    return suma;
}

#endif // INTERFAZ_TALLER_PROCESO_H
