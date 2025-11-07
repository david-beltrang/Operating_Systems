/*********************************************************************************************
 * Pontificia Universidad Javeriana
 *
 * Materia Sistemas Operativos
 * Docente: J. Corredor, PhD
 * Autor: Xamuel Perez
 * Fecha: 4/11/2025
 * Tema: OpenMP
 *
 * Descripción:
 *  - Calculo de la sumatoria de la funcion SENO
 *  - Para compilar se hace uso del FLAG
 *	interfaz matematica del GCC
 *	-lm
 * Se observa como la sumatoria siempre da el mismo resultado
 * sin importar el número de hilos con los que se ejecute
 * además de la mejora en el tiempo de ejecución al aumentar
 * el número de hilos.
 * Con esto se puede concluir que la paralelización es correcta
 * y que la función seno es independiente para cada valor
 * de i.
 *********************************************************************************************/
#include <omp.h>     // Header necesario para invocar API OpenMP
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))// Macro para obtener el mínimo entre dos valores

double f(int i) {// Función que calcula el seno de un valor basado en el índice
    int j;// Variable de control para el ciclo
    int start = i * (i + 1) / 2;// Cálculo del inicio del rango
    int finish = start + (i + 1);//(i + 1);// Cálculo del final del rango
    double return_val = 0;// Variable para acumular el resultado
    for (j = start; j < finish; j++)// Ciclo para sumar los valores de seno
        return_val += sin(j);// Suma el seno de j al acumulador
    return return_val;// Devuelve el valor acumulado
}

struct timeval inicio, fin;// Estructuras para medir el tiempo

void InicioMuestra(){// Función para iniciar la medición del tiempo
    gettimeofday(&inicio, NULL);// Obtiene el tiempo actual y lo almacena en 'inicio'
}

void FinMuestra(){// Función para finalizar la medición del tiempo e imprimir el resultado
    gettimeofday(&fin, NULL);// Obtiene el tiempo actual y lo almacena en 'fin'
    long sec  = fin.tv_sec  - inicio.tv_sec;// Calcula la diferencia en segundos
    long usec = fin.tv_usec - inicio.tv_usec;// Calcula la diferencia en microsegundos
    double tiempo = (double)sec + (double)usec / 1e6;// Convierte el tiempo total a segundos
    printf("Time elapsed : %.9f secs\n", tiempo);// Imprime el tiempo transcurrido  
}

int main(int argc, char *argv[]) {
    double sum = 0;// Variable para almacenar la sumatoria
    int i, n = 30000;// Variables de control y tamaño de la sumatoria

    if (argc != 2) {// Verifica que se haya proporcionado el número de hilos
        printf("Error \n\t$ ./ejecutable numHilos\n");// Mensaje de error si no se proporciona el número de hilos
        exit(0);// Sale del programa
    }

    int numHilos = atoi(argv[1]);// Convierte el argumento a entero
    omp_set_num_threads(numHilos);// Establece el número de hilos para OpenMP

    InicioMuestra(); // inicia medición del tiempo
    #pragma omp parallel// Inicia la región paralela
    {
        int threads = omp_get_num_threads();// Obtiene el número de hilos en la región paralela
        int max_hilos = omp_get_max_threads();// Obtiene el número máximo de hilos disponibles en el sistema
        #pragma omp master// Solo el hilo maestro ejecuta la siguiente línea
         printf("Number of threads is: %d\n", threads);
        //acumula la sumatoria de la funcion seno
        #pragma omp for reduction(+ : sum)//
        for (i = 0; i < n; i++) {// Ciclo for paralelo con reducción
            sum += f(i);// Suma el resultado de f(i) a la variable sum
        }
    }
    printf("The sum is: %.2f\n", sum);// Imprime el resultado de la sumatoria
    FinMuestra(); // termina medición e imprime tiempo

    return 0;
}