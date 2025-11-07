/********************************************************
*           Pontificia Universidad Javeriana            *
*                                                       *
*   Autor: David Esteban Beltrán Gómez                  *
*   Fecha: 4 Noviembre 2025                             *
*   Materia: Sistemas Operativos                        *
*   Tema: OpenMP                                        *
*   Descripción:                                        *
*    - Cálculo de la sumatoria de la función Sen        *
*    -Para compilar se hace uso del FLAG                *
*       Interfaz Matematica                             *
*********************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define MIN(x,y) (((x)<(y))? (x): (y))

double funcion(int i){
    // Calcula el inicio y el final del intervalo para el índice i
    int inicio = i * (i + 1) / 2;
    int final = inicio + 1;
    double valor = 0;

    // Acumula el valor de sen(i) en el intervalo definido
    for(int j = inicio; j < final; j++)
        valor += sin(i);

    return valor;
}

struct timeval inicio, fin;

void InicioMuestra(){
    // Registra el tiempo de inicio de la medición
    gettimeofday(&inicio, NULL);
}

void FinMuestra(){
    // Registra el tiempo final y calcula el tiempo transcurrido
    gettimeofday(&fin, NULL);
    long sec  = fin.tv_sec  - inicio.tv_sec;
    long usec = fin.tv_usec - inicio.tv_usec;
    double tiempo = (double)sec + (double)usec / 1e6;
    
    printf("Tiempo utilizado : %.9f segundos.\n", tiempo);
}

int main(int argc, char *argv[]) {
    double sumatoria = 0; // Variable acumuladora
    int i, n = 30000;     // Límite superior de la iteración

    // Validación del número de argumentos
    if (argc != 2) {
        printf("Error \n\t$ ./ejecutable numHilos\n");
        exit(0);
    }

    // Configuración de la cantidad de hilos a usar
    int numHilos = atoi(argv[1]);
    omp_set_num_threads(numHilos);

    InicioMuestra(); // Inicia medición del tiempo

    #pragma omp parallel
    {
        int threads = omp_get_num_threads();    // Hilos activos en la región paralela

        #pragma omp master
        printf("Numero de hilos implementados: %d\n", threads);

        // Distribuye el ciclo entre los hilos con reducción para evitar condición de carrera
        #pragma omp for reduction(+ : sumatoria)
        for (i = 0; i < n; i++) {
            sumatoria += funcion(i);
        }
    }

    // Muestra el resultado final
    printf("La suma es: %.2f\n", sumatoria);

    FinMuestra(); // Finaliza medición de tiempo

    return 0;
}