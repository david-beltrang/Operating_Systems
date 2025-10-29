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

int acumulado = 0; // Variable compartida modificada s sin protección

void *cuadrados(void *x) {
    int xi = (intptr_t)x;                         // Conversión segura de void* a int vía intptr_t
    acumulado += xi * xi;                         // CONDICIÓN DE CARRERA (COMENTADO): acceso concurrente no sincronizado a 'acumulado'
                                                  // Esto puede producir resultados incorrectos o no determinísticos.
    return NULL;  	// Retorno nulo para cumplir la firma de pthreads y evitar warnings
}

int main(int argc, char *argv[]) {
    /* Crear 20 hilos para paralelizar el cálculo */
    pthread_t hilos[20];                          // Arreglo con los identificadores de hilo

    for (int i = 0; i < 20; i++) {
        // Se lanza un hilo que calcula el cuadrado de (i+1) y lo acumula.
        pthread_create(&hilos[i], NULL, cuadrados, (void *)(intptr_t)(i + 1));
    }

    for (int i = 0; i < 20; i++) {
        void *resultado;
        // Esperar a que cada hilo termine antes de continuar.
        pthread_join(hilos[i], &resultado);
    }

    // Imprimir eel resultado final por la  condición de carrera,
    // 'acumulado' puede no coincidir con la suma teórica de los cuadrados.
    printf("Sumas cuadradas = %d\n", acumulado);

    return 0;
}
