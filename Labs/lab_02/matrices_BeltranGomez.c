/**************************************************************************************
 * Fecha: Agosto 12 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Generación de programa pricipal para la Multiplicación de Matrices
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas(Dimensión de filas es igual a la de columnas).
 * Inicialmente se genera el programa o código de forma general.
 * Posteriormente, se toma como enfoque la programación modular.
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h"

// Definir las variables globales
double *mA, *mB, *mC;
// Definir las estructuras de tiempo
struct timeval ini, fin;


int main(int argc, char *argv[]) {

    // Verificación de argumentos:
    if(argc<=2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }

    // Se le hace un cast al valor que el usuario ingresa para definir el tamaño de la matriz
    int N = (int) atof(argv[1]);
    // Verifica que N sea mayor que cero
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };

    // Se reserva memoria para las matrices A, B y C
    mA = (double *) malloc(N*N*sizeof(double)); 
    mB = (double *) malloc(N*N*sizeof(double)); 
    // Usando calloc se inicializan los elementos de la matriz C en cero
    mC = (double *) calloc(N*N,sizeof(double)); 

    // Se inicializan las matrices A y B
    iniMatriz(N, mA, mB);

    // Se imprimen las matrices A y B antes de multiplicar
    imprMatrices(N, mA);
    imprMatrices(N, mB);

    // Se realiza la multiplicación de las matrices A y B
     for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = mA + i*N;
            pB = mB + j;
            for(int k=0; k<N; k++, pA++, pB+=N){
                sumaTemp += *pA * *pB;
            }
            mC[j+i*N] = sumaTemp;
        }
    }
    // Se imprime la matriz
    imprMatrices(N, mC);

    printf("\n\tFin del programa.............!\n");
    // Se libera memoria, devolverle los recursos al sistema
    free(mA);
    free(mB);
    free(mC);
    return 0;

}