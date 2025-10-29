/************************************************************************************
 * Fecha: Octubre 28 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Hilos con API POSIX
 * Descripción: Crear tres hilos que ejecutan una tarea simulado y muestran resultados.
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER; // Variable de condición inicializada
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex inicializado para coordinar con la condición

int valor = 100;            // Valor compartido leído/escrito por los hilos
bool notificar = false;     // Señal para indicar actualización de 'valor'

void *reportar(void *nousado) {
/*
    pthread_mutex_lock(&mutex);
    while (!notificar) {
        pthread_cond_wait(&var_cond, &mutex);
    }
*/
    printf("El valor es: %d\n", valor);
/*
    pthread_mutex_unlock(&mutex);
*/
    return NULL;  /* Nada que retornar; se previene la advertencia <warning> */
}

void *asignar(void *nousado) {
    valor = 20;
/*
    pthread_mutex_lock(&mutex);
    notificar = true;
    pthread_cond_signal(&var_cond);
    pthread_mutex_unlock(&mutex);
*/
    return NULL;  /* Nada que retornar; se previene la advertencia <warning> */
}

int main(int argc, char *argv[]) {
    pthread_t reporte, asigne; // Identificadores de hilos: 'reporte' imprime, 'asigne' modifica

    pthread_create(&reporte, NULL, reportar, NULL); // Crear hilo 'reporte'
    pthread_create(&asigne, NULL, asignar, NULL);   // Crear hilo 'asigne'

    void *nousado; // Puntero usado para recibir valores de pthread_join

    pthread_join(reporte, &nousado); // Esperar a que termine 'reporte'
    pthread_join(asigne, &nousado);  // Esperar a que termine 'asigne'

    return 0; // Finaliza proceso
}
