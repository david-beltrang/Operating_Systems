#ifndef OPERACIONES_HILOS_H
#define OPERACIONES_HILOS_H

#include <pthread.h>

// Estructura para pasar parámetros a los hilos
struct parametros {
    int idH;    // ID del hilo
    int nH;     // Número total de hilos
    int N;      // Tamaño de la matriz
};

// Función que multiplica las matrices en paralelo usando hilos
void *multiMatrix(void *variables);

#endif // OPERACIONES_HILOS_H