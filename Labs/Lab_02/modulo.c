/*************************************************************************************
 * Fecha: Agosto 12 del 2025                                                         *
 * Autor: David Beltrán Gómez                                                        *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Generación de programa pricipal para la Multiplicación de Matrices          *
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "modulo.h" // Incluye el archivo de cabecera modulo.h


// En este archivo se implementan las funciones declaradas en el archivo modulo.h

// Obtiene el tiempo de inicio de la ejecución usando gettimeofday para obtener el tiempo en microsegundos
void InicioMuestra(){
        gettimeofday(&ini, (void *)0);
}

// Obtiene el tiempo de fin de la ejecución y calcula la diferencia con el tiempo de inicio
void FinMuestra(){
        gettimeofday(&fin, (void *)0);
        fin.tv_usec -= ini.tv_usec;
        fin.tv_sec -= ini.tv_sec;
        double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
        printf("%9.0f \n", tiempo);
}

// Inicializa las matrices A y B con valores específicos
void iniMatriz(int n, double *m1, double *m2){
        for(int i=0; i<n*n; i++){
                m1[i] = i*2.3 + 1.3;
                m2[i] = i*2.3;
        }
};

// Imprime la matriz si su tamaño es menor que 9x9, de lo contrario solo imprime una línea divisoria
void imprMatrices(int n, double *matriz){
    if(n<9){
        printf("\n#######################################################\n");
        for(int i=0; i<n*n; i++){
                if(i%n==0) printf("\n");
                printf(" %f ", matriz[i]);
   }
    } else {
        printf("\n#######################################################\n");
    }
};