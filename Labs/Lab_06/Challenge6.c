/************************************************************************************
 * Fecha: Octubre 28 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Verificación con mutex-lock-unlock
 * Descripción: Crear tres hilos que ejecutan una tarea simulado y muestran resultados.
*************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>

int acumulado = 0;                               // Variable compartida para la suma de cuadrados
pthread_mutex_t acumuladoMutex = PTHREAD_MUTEX_INITIALIZER; // Mutex que protege 'acumulado'

void *cuadrados(void *x) {
    int xi = (intptr_t)x;                        // Convertir el argumento void* a entero (xi)
    pthread_mutex_lock(&acumuladoMutex);         // BLOQUEO: proteger la sección crítica antes de modificar 'acumulado'
    acumulado += xi * xi;                        // ACCESO PROTEGIDO: actualización de 'acumulado' (no hcay condición de carrera aquí)
    pthread_mutex_unlock(&acumuladoMutex);       // DESBLOQUEO: liberar mutex después de la actualización
    return NULL;  /* Retorno nulo para cumplir la firma de pthreads y evitar warnings */
}

int main(int argc, char *argv[]) {
    /* Se crean 20 hilos, inicializamos */
    pthread_t hilos[20];                          // Array de identificadores de hilos

    for (int i = 0; i < 20; i++) {
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i + 1)); // Crear hilo i con argumento (i+1)
    }

    for (int i = 0; i < 20; i++) {
        void *resultado;
        pthread_join(hilos[i], &resultado);      // Esperar a que cada hilo termine
    }

    printf("Sumas cuadradas = %d\n", acumulado);  // Imprimir resultado acumulado

    return 0;
}
