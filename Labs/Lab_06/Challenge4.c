/************************************************************************************
 * Fecha: Octubre 28 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Verificación con mutex-lock-unlock
 * Descripción: Crear tres hilos que ejecutan una tarea simulado y muestran resultados.
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_t tid[3];    // Array de identificadores de los 3 hilos
int counter = 0;     // Contador compartido entre hilos

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para proteger 'counter'

void* compute(void *arg) {
    unsigned long i = 0;                 // Variable para el bucle de trabajo
    int idjoblocal;

    pthread_mutex_lock(&counter_mutex);  // Proteger incremento y lectura de 'counter'
    counter += 1;                        // Aumentar contador compartido
    idjoblocal = counter;                      // Guardar id del job localmente
    pthread_mutex_unlock(&counter_mutex); // Liberar mutex

    printf("\n Job %d has started\n", idjoblocal); // Mostrar inicio del trabajo con número de job

    for (i = 0; i < (0xFFFFFFF); i++);   // Bucle de espera para simular trabajo

    printf("\n Job %d has finished\n", idjoblocal); // Mostrar finalización usando el id

    return NULL;                         // Retornar NULL al hilo que finaliza
}

int main(void) {
    int i = 0;                           // Índice para crear hilos
    int error;                           // Código de error devuelto por pthread_create

    while (i < 3) {
        error = pthread_create(&(tid[i]), NULL, &compute, NULL); // Crear hilo i ejecutando compute
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error)); // Mostrar error si falla al crear
        i++;
    }

    pthread_join(tid[0], NULL);          // Esperar a que termine el hilo 0
    pthread_join(tid[1], NULL);          // Esperar a que terminel hilo 1
    pthread_join(tid[2], NULL);  	 // Esperar a que terminel hilo 2

    return 0;                            // Finalizar el programa exitosamente
}
