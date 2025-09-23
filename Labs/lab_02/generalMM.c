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
#include <time.h>


// Crear matriz NxN
float** crearMatriz(int N) {
    // Crear matriz NxN 
    float** matriz = (float**)malloc(N * sizeof(float*));
    // Asignar memoria a cada fila
    for (int i = 0; i < N; i++) {
        matriz[i] = (float*)malloc(N* sizeof(float));
    }
    return matriz;
}

// Llenar matriz con valores aleatorios
void llenarMatrix(int N, float** mA) {
    // Llenar matriz con valores aleatorios
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // Generar valores aleatorios entre 0 y 100
            mA[i][j] = (float)(rand() % 100) * 0.1f;
        }
    }
}

// Imprimir matriz
void imprimirMatrix(float** mA, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", mA[i][j]);
        }
        printf("\n");
    }
}

// Multiplicar matrices
float** MultiplicarMatrix(float** mA, float** mB, int N) {
    // Crear matriz resultado
    float** mC = crearMatriz(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mC[i][j] = 0.0;
            for (int k = 0; k < N; k++) {
                mC[i][j] += mA[i][k] * mB[k][j];
            }
        }
    }
    return mC;
}

// Liberar memoria
void liberarMatriz(float** matriz, int N) {
    // Liberar memoria de cada fila
    for (int i = 0; i < N; i++) {
        free(matriz[i]);
    }
    // Liberar memoria de la matriz
    free(matriz);
}

// Calcular IMC
float calcularIMC(float masa, float altura) {
    return masa / (altura * altura);
}

// Categorizar la edad segun su rango 
char* categoriaEdad(int edad) {
    if (edad < 18) {
        return "Menor de edad";
    } else if (edad < 50) {
        return "Adulto";
    } else {
        return "Tercera edad";
    }
}

// Imprime Menú principal
void mostrarMenu() {
    printf("\n          MENU\n");
    printf("1. Calcular IMC\n");
    printf("2. Multiplicar matrices aleatorias\n");
    printf("3. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int opcion;
    // Inicializar la semilla para números aleatorios
    srand(time(NULL)); 

    do {
        // Mostrar menú en pantalla
        mostrarMenu();
        // Leer opción del usuario
        scanf("%d", &opcion);

        switch (opcion) {
            // Caso 1: Calcular IMC
            case 1: {
                printf("\n  CALCULADOR DE IMC\n");
                float masa, altura;
                int edad;

                printf("Ingrese su masa (kg): ");
                scanf("%f", &masa);
                printf("Ingrese su altura (m): ");
                scanf("%f", &altura);
                printf("Ingrese su edad (años): ");
                scanf("%d", &edad);

                float imc = calcularIMC(masa, altura);
                char* categoriaE = categoriaEdad(edad);

                printf("Su IMC es: %.2f\n", imc);
                printf("Se encuentra en la categoria de edad: %s\n", categoriaE);
                break;
            }

            // Caso 2: Multiplicar matrices aleatorias
            case 2: {
                int N;
                printf("Ingrese el tamaño de las matrices (NxN): ");
                scanf("%d", &N);

                float** mA = crearMatriz(N);
                float** mB = crearMatriz(N);

                llenarMatrix(N, mA);
                llenarMatrix(N, mB);

                printf("\nMatriz A:\n");
                imprimirMatrix(mA, N);

                printf("\nMatriz B:\n");
                imprimirMatrix(mB, N);

                float** mC = MultiplicarMatrix(mA, mB, N);
                printf("\nResultado de A x B:\n");
                imprimirMatrix(mC, N);

                liberarMatriz(mA, N);
                liberarMatriz(mB, N);
                liberarMatriz(mC, N);
                break;
            }

            // Caso 3: Salir
            case 3:
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opcion inválida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != 3);

    return 0;
}