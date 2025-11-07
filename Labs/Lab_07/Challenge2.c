/********************************************************
*           Pontificia Universidad Javeriana            *
*                                                       *
*   Autor: David Esteban Beltrán Gómez                  *
*   Fecha: 4 Noviembre 2025                             *
*   Materia: Sistemas Operativos                        *
*   Tema: OpenMP                                        *
*   Descripción:                                        *
*	    -Introduccion en laboratiorio de OPENMP         *
* 	    -Clausulas y directivas para el programa        *
*       - Uso de la directiva parallel                  *
*********************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    /* Verifica que el usuario ingresó exactamente 1 argumento (el número de hilos). 
       Si puso menos o más, muestra un mensaje de error y termina la ejecución. */
    if(argc != 2){
        printf("Error \n\t$./ejecutable numHilos\n\n");
        exit(0);
    }
    else {
        /* Convierte el argumento recibido (texto) a un entero, 
           que es el número de hilos a utilizar. */
        int numHilos = (int) atoi(argv[1]);

        // Muestra el número de hilos solicitado por el usuario
        printf("===== %d === \n", numHilos);

        // Obtiene la cantidad máxima de hilos que puede usar el sistema teniendo en cuenta el Hardware
        int maxHilos = omp_get_max_threads();
        printf("OpenMP ejecutando en Cores(HiperThreading)= %d hilos\n", maxHilos);

        // Establece el número de hilos que OpenMP utilizará en las regiones paralelas
        omp_set_num_threads(numHilos);

        // El código dentro de los corchetes será ejecutado por cada hilo creado de manera paralela
        #pragma omp parallel
        {
            // Cada hilo imprime un mensaje indicando su identificador (ID interno)
            printf("Hello World desde el thread %d\n", omp_get_thread_num());
        }
    }

    // Fin del programa
    return 0;
}
