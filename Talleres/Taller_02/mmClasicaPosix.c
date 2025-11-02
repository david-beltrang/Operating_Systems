/*#######################################################################################
#* Fecha: 30 Octubre 2025
#* Autor: David Beltrán Gómez
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "operacionesMatrices.h"
#include "operacionesHilos.h"
#include "operacionesTiempo.h"

pthread_mutex_t MM_mutex;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        exit(0);
    }

    int N = atoi(argv[1]);
    int n_threads = atoi(argv[2]);

    pthread_t p[n_threads];
    pthread_attr_t atrMM;

    double *matrixA = (double *)calloc(N * N, sizeof(double));
    double *matrixB = (double *)calloc(N * N, sizeof(double));
    double *matrixC = (double *)calloc(N * N, sizeof(double));

    // Inicializa las matrices con valores aleatorios
    iniMatrix(matrixA, matrixB, N);

    // Imprime las matrices iniciales
    impMatrix(matrixA, N, 0);
    impMatrix(matrixB, N, 1);

    // Inicia la medición de tiempo
    InicioMuestra();

    // Inicializa el mutex
    pthread_mutex_init(&MM_mutex, NULL);

    // Configura los atributos de los hilos
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Crea los hilos para realizar la multiplicación
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *)malloc(sizeof(struct parametros));
        datos->idH = j;
        datos->nH = n_threads;
        datos->N = N;

        pthread_create(&p[j], &atrMM, multiMatrix, (void *)datos);
        // Liberar memoria de la estructura datos
        free(datos);
    }

    // Espera que terminen todos los hilos
    for (int j = 0; j < n_threads; j++) {
        pthread_join(p[j], NULL);
    }

    // Finaliza la medición de tiempo
    FinMuestra();

    // Imprime la matriz resultante
    impMatrix(matrixC, N, 0);

    // Liberación de Memoria
    free(matrixA);
    free(matrixB);
    free(matrixC);

    // Destruye los atributos de los hilos y el mutex
    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);

    pthread_exit(NULL);

    return 0;
}