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
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 * *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double *mA, *mB, *mC;

// Function to print matrices
void imprMatrices(int n, double *matriz){
    if(n<9){
        printf("\n#######################################################\n");
    } else {
        printf("\n#######################################################\n");
    }
};

   for(int i=0; i<n*n; i++){
                if(i%n==0) printf("\n");
        printf(" %f ", matriz[i]);
   }


int main(int argc, char *argv[]){
    if(argc<=2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }

    int N = (int) atof(argv[1]);
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };


    mA = (double *) malloc(N*N*sizeof(double));
    mB = (double *) malloc(N*N*sizeof(double));
    mC = (double *) calloc(N*N*sizeof(double));

    // Initialize matrices with a random numbers
    for(int i=0; i<N*N;i++){
        mA[i]= (double) rand() / RAND_MAX;
        mB[i]= (double) rand() / RAND_MAX;
    }

    // Initialize pointers for matrix multiplication
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double sumaTemp, *pA, *pB;
            sumaTemp = 0.0;
            pA = mA + i*n;
            pB = mB + j;
            for(int k=0; k<N; k++, pA++, pB+=n){
                sumaTemp += *pA * *pB;
            }
            mC[j+i*n] = sumaTemp;
        }
    }

    // Print all the matrices
    imprMatrices(N, mA);
    imprMatrices(N, mB);
    imprMatrices(N, mC);

    printf("\n\tFin del programa.............!\n");
    
    // Free allocated memory
    free(mA);
    free(mB);
    free(mC);
    return 0;
}