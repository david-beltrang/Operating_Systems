/****************************************************************
*           Pontificia Universidad Javeriana                    *
*                                                               *
*   Autor: David Esteban Beltrán Gómez                          *
*   Fecha: 4 Noviembre 2025                                     *
*   Materia: Sistemas Operativos                                *
*   Tema: OpenMP                                                *
*   Descripción:                                                *
*	    - Ejemplo de uso de variables privadas y compartidas    *
*       - Uso de la directiva parallel                          *
*****************************************************************/

#include <omp.h> 
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Declaración e Inicialización de Variables
    int i;
    const int N = 1000; // Límite superior del bucle
    int a = 50;         // Variable inicializada: 50
    int b = 0;          // Variable inicializada: 0

    /*
        Directiva de Paralelismo y Bucles:
            #pragma omp parallel for: Crea el equipo de hilos y distribuye las iteraciones del bucle 'for'
            entre ellos automáticamente.

            private(i): i es el contador del bucle y debe ser privado para cada hilo.
            private(a): Cada hilo recibe su propia copia local de 'a'
            La variable 'b' es de tipo 'shared'
    */
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++){
        // Ocurre una race condition:
        // Múltiples hilos intentan leer y escribir en la variable compartida 'b'
        // al mismo tiempo, llevando a un resultado incorrecto e impredecible.
        b = a + i; // Escritura concurrente en 'b'
    }

    // La 'a' original sigue siendo 50. 'b' puede no ser 1049 por la condición de carrera.
    printf("a = %d b = %d (Se espera a=50 b = 1049)\n", a, b);

    return 0;
}