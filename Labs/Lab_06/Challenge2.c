/************************************************************************************
 * Fecha: Octubre 7 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Hilos con API POSIX
 * Descripción: Programa cra 10 hilos POSIX. Cada hilo
 *   imprime su número y el ID del hilo y luego incrementa un
 *   contador global protegido por un mutex.
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NHILOS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;   // Declara e inicializa un mutex global
int counter = 0;                                     // Variable global compartida por los hilos

// Función que va a ejecutar cada hilo
void *funcion(void *arg){
    int i = *(int *)arg;                             // Convierte el argumento recibido a int
    printf("Numero de hilo: %d | Id hilo: %ld\n", i, pthread_self()); // Imprime número el ID del hilo

    pthread_mutex_lock(&mutex);                      // Bloquea el mutex para evitar Condicion de Carrera
    counter++;                                       // Incrementa el contador global de forma segura
    pthread_mutex_unlock(&mutex);                    // Desbloquea el mutex, permitiendo que otro hilo acceda

    return NULL;                                     // Termina la función del hilo
}

int main(){
    pthread_t hilo_ID[NHILOS];                       // Arreglo para almacenar los identificadores de los hilos
    int i;                                           // Variable para el índice del bucle(moverse en los hilos)

    for(i = 0; i < NHILOS; i++)                      // Bucle para crear NHILOS hilos
        pthread_create(&hilo_ID[i], NULL, funcion, &i); // Crea cada hilo, pasándole la funcion y el valor de 'i' como argumento

    printf("Contador final: %d\n", counter);         // Imprime el valor final del contador
    return 0;                                        // Termina el programa correctamente
}
