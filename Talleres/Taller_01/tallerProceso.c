/************************************************************************************
 * Fecha: Octubre 27 del 2025
 * Autores: David Beltrán Gómez, Juan Felipe Gomez Lopez y Xamuel Perez Madrigal
 * Materia: Sistemas Operativos
 * Tema: Taller 2 Procesos
*************************************************************************************/
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "interfazTallerProceso.h"

int main(int argc, char *argv[]) {
    /* Verificar que se lean los 5 argumentos */
    if (argc != 5) {
        printf("Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return 1;
    }

    /* Guardar cada uno de los datos en sus respectivas variables */
    int N1 = atoi(argv[1]);
    char *archivo00 = argv[2];
    int N2 = atoi(argv[3]);
    char *archivo01 = argv[4];

    /* Reservar memoria dinámica */
    int *arreglo1 = (int *)malloc(N1 * sizeof(int));
    int *arreglo2 = (int *)malloc(N2 * sizeof(int));

    /* Verificar si se pudo reservar memoria correctamente */
    if (!arreglo1 || !arreglo2) {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }

    // Leer los archivos usando la funcion de la interfaz
    leerArchivo(archivo00, arreglo1, N1);
    leerArchivo(archivo01, arreglo2, N2);

    // Crear pipes para comunicación entre los procesos
    int pipe1[2], pipe2[2], pipe3[2];

    /* Crear el pipe1 y verificar si se crearo correctamente */
    if (pipe(pipe1) == -1) {
        perror("ERROR al crear el pipe 1.");
        exit(EXIT_FAILURE);
    }

    /* Crear el pipe2 y verificar si se crearo correctamente */
    if (pipe(pipe2) == -1) {
        perror("ERROR al crear el pipe 2.");
        exit(EXIT_FAILURE);
    }

    /* Crear el pipe3 y verificar si se crearo correctamente */
    if (pipe(pipe3) == -1) {
        perror("ERROR al crear el pipe 3.");
        exit(EXIT_FAILURE);
    }

    /* Variables para guardar los ID de cada proceso */
    pid_t pPrimerHijo_PID, pSegundoHijo_PID, pNieto_PID;

    // Primer hijo: suma total general
    pPrimerHijo_PID = fork();
    if (pPrimerHijo_PID == 0) {  // Hijo 1
        close(pipe1[0]); // Cerrar lectura en pipe1
        int sumaTotal = sumarArreglo(arreglo1, N1) + sumarArreglo(arreglo2, N2);
        printf("Hijo 1 (suma total): %d\n", sumaTotal);  // Mensaje de depuración
        write(pipe1[1], &sumaTotal, sizeof(int)); // Escribir en pipe1
        close(pipe1[1]);
        exit(0);
    }

    // Segundo hijo: calcula sumaB
    pSegundoHijo_PID = fork();
    if (pSegundoHijo_PID == 0) {  // Hijo 2
        close(pipe2[0]); // Cerrar lectura en pipe2
        int sumaB = sumarArreglo(arreglo2, N2);
        printf("Hijo 2 (suma B): %d\n", sumaB);  // Mensaje de depuración
        write(pipe2[1], &sumaB, sizeof(int)); // Escribir en pipe2
        close(pipe2[1]);
        exit(0);
    }

    // Nieto: calcula sumaA
    pNieto_PID = fork();
    if (pNieto_PID == 0) {  // Nieto
        close(pipe3[0]); // Cerrar lectura en pipe3
        int sumaA = sumarArreglo(arreglo1, N1);
        printf("Nieto (suma A): %d\n", sumaA);  // Mensaje de depuración
        write(pipe3[1], &sumaA, sizeof(int)); // Escribir en pipe3
        close(pipe3[1]);
        exit(0);
    }

    // Proceso padre: recibe resultados
    close(pipe1[1]);
    close(pipe2[1]);
    close(pipe3[1]);

    int sumaTotal, sumaB, sumaA;

    // Leer de los pipes
    read(pipe1[0], &sumaTotal, sizeof(int)); // Leer de pipe1
    printf("Padre: leí suma total: %d\n", sumaTotal);  // Mensaje de depuración
    read(pipe2[0], &sumaB, sizeof(int)); // Leer de pipe2
    printf("Padre: leí suma B: %d\n", sumaB);  // Mensaje de depuración
    read(pipe3[0], &sumaA, sizeof(int)); // Leer de pipe3
    printf("Padre: leí suma A: %d\n", sumaA);  // Mensaje de depuración

    close(pipe1[0]);
    close(pipe2[0]);
    close(pipe3[0]);

    // Esperar a que los hijos y el nieto terminen
    waitpid(pPrimerHijo_PID, NULL, 0);
    waitpid(pSegundoHijo_PID, NULL, 0);
    waitpid(pNieto_PID, NULL, 0);

    // Imprimir los resultados finales
    printf("Resultados finales:\n");
    printf("Suma total (hijo 1): %d\n", sumaTotal);
    printf("Suma B (hijo 2): %d\n", sumaB);
    printf("Suma A (nieto): %d\n", sumaA);

    // Liberar memoria
    free(arreglo1);
    free(arreglo2);

    return 0;
}
