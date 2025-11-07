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
*       -Ejemplo básico de paralelización con OpenMP    *
*********************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    // Obtener el número máximo de hilos disponibles que OpenMP puede utilizar
    int maxHilos = omp_get_max_threads();

    // Mostrar la cantidad de hilos con la que se ejecutará el programa
    printf("OpenMP ejecutando con %d hilos\n", maxHilos);
    
    // Sección paralela: Todo lo que está dentro de los corchetes se ejecutará de manera paralela
    #pragma omp parallel
    {
        // Cada hilo imprime un mensaje identificándose con su número (ID del hilo)
        // omp_get_thread_num() devuelve el ID único del hilo dentro del equipo
        printf("Hello World desde el thread %d\n", omp_get_thread_num());
    }

    // Fin del programa
    return 0;
}