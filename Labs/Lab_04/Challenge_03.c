/************************************************************************************
 * Fecha: Octubre 7 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 3
*************************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    /* Imprimir mensaje de inicio del proceso principal */
    printf("=== Inicio del proceso principal ===\n");

    /* Creacion de un Pipe o tuberia para comunicacion entre procesos */
    int pipefd[2]; /* pipefd[0] es el descriptor para lectura, pipefd[1] para escritura */

    /* Crear una variable para guardar el ID del proceso hijo */
    pid_t pHIJO_PID;

    /* Se crea el pipe con la funcion pipe() que retorna 0 si se ha creado el pipe correctamente */
    if(pipe(pipefd) == -1){
        perror("ERROR al crear el pipe");
        exit(EXIT_FAILURE);
    }

    /* Llamada al fork: Creacion de proceso */
    pHIJO_PID = fork();

    /* Verificar error al crear el proceso hijo */
    if(pHIJO_PID == -1){
        perror("ERROR al ejecutar fork");
        exit(EXIT_FAILURE);
    }

    /* Se verifica si fork() retorno 0 para saber si es proceso hijo */
    if(pHIJO_PID == 0){
        /* Se cierra el descriptor del pipe para el padre */
        close(pipefd[1]);

        /* Se reserva espacio para la cadena de caracteres que recibira el hijo */
        char mensaje[100];
        int lectBytes;

        /* Se lee el mensaje desde el descriptor del Pipe */
        lectBytes = read(pipefd[0], mensaje, sizeof(mensaje));

        /* Se verifica si la lectura fue exitosa */
        if(lectBytes == -1){
            perror("ERROR en lectura del hijo");
            exit(EXIT_FAILURE);
        }

        /* Se imprime en pantalla el mensaje recibido */
        printf("\t#=== Proceso HIJO: recibe mensaje del PADRE %.*s ##\n", lectBytes, mensaje);

        /* Se cierra el descriptor del pipe para el hijo */
        close(pipefd[0]);
    }
    else {
        /* Se cierra el descriptor del pipe para el hijo */
        close(pipefd[0]);

        /* Se crea un mensaje para enviar al hijo */
        char mensajeP[] = "Hola soy tu PADRE LUKE!!!";
        int escrBytes;

        /* Se escribe el mensaje haciendo una escritura en el descriptor del pipe */
        escrBytes = write(pipefd[1], mensajeP, strlen(mensajeP));

        /* Se verifica si la escritura fue exitosa */
        if(escrBytes == -1){
            perror("ERROR en escritura del padre");
            exit(EXIT_FAILURE);
        }

        /* Se cierra el descriptor del pipe para el padre */
        close(pipefd[1]);
    }

    /* Ambos procesos ejecutan esta línea */
    printf("FIN...........\n");

    return 0;
}