/************************************************************************************
 * Fecha: Octubre 28 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Hilos con POSIX
 * Descripción: Crear un hilo que reporta un valor y otro que lo asigna.
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stdbool.h>

pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER; // Variable de condición inicializada
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex inicializado para coordinar con var_cond

int valor = 100;            // Valor compartido leído/escrito por los hilos
bool notificar = false;     // Señal para indicar actualización de 'valor'

void *reportar(void *nousado) {
    pthread_mutex_lock(&mutex);               // Bloquear mutex antes de comprobar 'notificar' / acceder a 'valor'
    while (!notificar) {                      // Esperar mientras no se haya producido la señal
        pthread_cond_wait(&var_cond, &mutex); // Espera de condición: libera mutex y bloquea el hilo hasta señal
    }

    printf("El valor es: %d\n", valor);       // Acceso a 'valor' protegido por mutex (lectura sincronizada)

    pthread_mutex_unlock(&mutex);             // Desbloquear mutex tras acceder a la sección crítica

    return NULL;  /* Nada que retornar; se previene la advertencia <warning> */
}

void *asignar(void *nousado) {
    valor = 20;                               // Asignación local antes de señal                                              // En este código la asignación se realiza antes de bloquear; mejor moverla dentro del mutex.
    pthread_mutex_lock(&mutex);               // Bloquear mutex antes de actualizar 'notificar' y señalizar
    notificar = true;                         // Marcar que el valor fue actualizado (estado protegido por mutex)
    pthread_cond_signal(&var_cond);           // Señalizar a hilo en espera que pueden continuar
    pthread_mutex_unlock(&mutex);             // Desbloquear mutex tras señalizar

    return NULL;  /* Nada que retornar; se previene la advertencia <warning> */
}

int main(int argc, char *argv[]) {
    pthread_t reporte, asigne;                // Identificadores de hilos: 'reporte' imprime, 'asigne' modifica

    pthread_create(&reporte, NULL, reportar, NULL); // Crear hilo 'reporte'
    pthread_create(&asigne, NULL, asignar, NULL);   // Crear hilo 'asigne'

    void *nousado;                            // Puntero usado para recibir valores de pthread_join

    pthread_join(reporte, &nousado);          // Esperar a que termine 'reporte'
    pthread_join(asigne, &nousado);           // Esperar a que termine 'asigne'

    return 0;
}
