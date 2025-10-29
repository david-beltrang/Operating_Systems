/**************************************************************
* Fecha: Octubre 28 del 2025
* Autor: David Beltrán Gómez
* Materia: Sistemas Operativos
* Tema: Exlusion mutua, mutex en POSIX
* Descripción: Muestra como el uso de mutex y variables de condición
* para sincronizar hilos que incrementan un mismo contador
**************************************************************/
#include <stdio.h>     
#include <stdlib.h>    
#include <pthread.h>   

/* Mutex para proteger la sección crítica sobre 'count' */
pthread_mutex_t count_mutex      = PTHREAD_MUTEX_INITIALIZER;
/* Mutex usado junto a la variable de condición para coordinar espera/señal */
pthread_mutex_t condition_mutex  = PTHREAD_MUTEX_INITIALIZER;
/* Variable de condición para sincronizar los hilos según el valor de 'count' */
pthread_cond_t  condition_cond   = PTHREAD_COND_INITIALIZER;

/* Contador compartido entre hilos */
int count = 0;

#define COUNT_DONE  15    // Valor objetivo para terminar la ejecución
#define COUNT_HALT1  4    // Límite inferior del intervalo en el que un hilo espera
#define COUNT_HALT2 11    // Límite superior del intervalo en el que un hilo espera

void *count01() {
    for(;;) {                                       // Bucle infinito que terminará al alcanzar COUNT_DONE
        pthread_mutex_lock( &condition_mutex );    // Bloquear mutex de condición antes de comprobar 'count'
        while ( count >= COUNT_HALT1 && count <= COUNT_HALT2 )
        {
            pthread_cond_wait( &condition_cond, &condition_mutex ); // Esperar señal mientras 'count' esté en [HALT1, HALT2]
        }
        pthread_mutex_unlock( &condition_mutex );  // Desbloquear mutex de condición tras la espera/comprobación

        pthread_mutex_lock( &count_mutex );        // Bloquear mutex de contador antes de modificar 'count'
        count++;                                   // Incrementar el contador compartido
        printf("Counter value functionCount == 01 <==: %d\n", count); // Imprimir el valor actualizado
        pthread_mutex_unlock( &count_mutex );      // Desbloquear mutex de contador

        if(count >= COUNT_DONE) return(NULL);      // Finalizar el hilo si se alcanzó el objetivo
    }
}

void *count02() {
    for(;;) {                                       // Bucle infinito que terminará al alcanzar COUNT_DONE
        pthread_mutex_lock( &condition_mutex );    // Bloquear mutex de condición antes de comprobar 'count'
        if( count < COUNT_HALT1 || count > COUNT_HALT2 )
        {
            pthread_cond_signal( &condition_cond ); // Señalar a hilos en espera si 'count' está fuera del intervalo
        }
        pthread_mutex_unlock( &condition_mutex );  // Desbloquear mutex de condición tras la comprobación/señal

        pthread_mutex_lock( &count_mutex );        // Bloquear mutex de contador antes de modificar 'count'
        count++;                                   // Incrementar el contador compartido
        printf("Counter value functionCount == 02 <==: %d\n", count); // Imprimir el valor actualizado
        pthread_mutex_unlock( &count_mutex );      // Desbloquear mutex de contador

        if(count >= COUNT_DONE) return(NULL);      // Finalizar el hilo si se alcanzó el objetivo
    }
}

void main() {
    pthread_t thread1, thread2;                    // Identificadores para los dos hilos
    pthread_create( &thread1, NULL, &count01, NULL ); // Crear hilo 1 que ejecuta count01
    pthread_create( &thread2, NULL, &count02, NULL ); // Crear hilo 2 que ejecuta count02
    pthread_join( thread1, NULL );                 // Esperar a que termine el hilo 1
    pthread_join( thread2, NULL );                 // Esperar a que termine el hilo 2
    exit(0);                                       // Salir del programa
}
