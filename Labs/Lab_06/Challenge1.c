/************************************************************************************
 * Fecha: Octubre 28 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 1
 * Descripción: Programa de ejemplo que crea dos Hilos POSIX para imprimir un mensaje.
*************************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Función que ejecutará cada hilo creado
void *print_message_function(void *ptr) {
    char *message;                  // Declara un puntero a char para almacenar el mensaje
    message = (char *) ptr;         // Convierte el puntero recibido a tipo (char*)
    printf("%s \n", message);       // Imprime el mensaje ("Thread 1" o "Thread 2")
}

void main() {
    pthread_t thread1, thread2;     // Declara dos variables de tipo pthread_t para los dos hilos
    char *message1 = "Thread 1";    // Define el mensaje para el primer hilo
    char *message2 = "Thread 2";    // Define el mensaje para el segundo hilo
    int iret1, iret2;               // Variables que guardarán el valor de retorno de pthread_create

    /* Crea hilos independientes, cada uno ejecutará la misma función con diferentes mensajes */
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*) message1); // Crea el hilo 1
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*) message2); // Crea el hilo 2

    printf("Thread 1 returns: %d\n", iret1);  // Muestra el valor de retorno de la creación del hilo 1 (0 si fue exitosa)
    printf("Thread 2 returns: %d\n", iret2);  // Muestra el valor de retorno de la creación del hilo 2 (0 si fue exitosa)

    exit(0);   // Finaliza el programa.
}
