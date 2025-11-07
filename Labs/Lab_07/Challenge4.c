/****************************************************************
*           Pontificia Universidad Javeriana                    *
*                                                               *
*   Autor: David Esteban Beltrán Gómez                          *
*   Fecha: 4 Noviembre 2025                                     *
*   Materia: Sistemas Operativos                                *
*   Tema: OpenMP                                                *
*   Descripción:                                                *
*       - Introduccion en laboratorio de OPENMP                 *
*       - Clausulas y directivas para el programa               *
*       - Ejemplo de uso de variables privadas y compartidas    *
*   Se elimina la condición de carrera al hacer 'b' privada     *
*****************************************************************/


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int i;
    const int N = 1000;
    int a = 50;
    int b = 0;

    /*
       Región paralela con bucle distribuido entre los hilos:
       - private(i): cada hilo maneja su propio índice sin interferir.
       - private(a): cada hilo usa una copia de 'a', no modifica la original.
       - private(b): cada hilo tiene su propio 'b', por lo tanto el cálculo de b = a+i
                     ocurre independientemente en cada hilo y no se refleja fuera del for.
       Al declarar 'b' como private, evita el Race Condition y hace que el valor concuerde con el calculo.
    */
    #pragma omp parallel for private(i) private(a) private(b)
    for (i = 0; i < N; i++){
        b = a + i; // Cada hilo calcula su propio b, sin afectar el b global
    }

    // Imprime en pantalla los valores de a y b. Al lado de los esperados
    printf("a = %d b = %d (Se espera a=50 b = 0)\n", a, b);

    return 0;
}
