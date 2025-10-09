/************************************************************************************
 * Fecha: Octubre 7 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 2
*************************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


/************************************************************************************
 * Nota:
 * El orden de impresion en los procesos padre e hijo no tiene un orden garantizado,
 * debido a que ambos procesos se ejecutan de manera concurrente después del fork() 
 * Por esto al ejecutarlo a veces en consola se ven combinados los mensajes impresos
 * por el proceso padre y el hijo, para evitar esto se debe utilizar wait() en el
 * proceso padre para esperar que el hijo termine antes de continuar.
 ************************************************************************************/


int main(){
    /* Imprimir mensaje de inicio del proceso principal */
    printf("=== Inicio del proceso principal ===\n");
    /* Se crea un proceso usando la funcion fork() que retorna el ID del proceso*/
    int procesoID = fork();
    /* Se verifica si fork() retorno un valor positivo o negativo para saber si es proceso padre o hijo */
    if(procesoID==0){
        /* Se imprime el ID del proceso hijo */
        printf("---> Proceso hijo recien creado con ID %d \n", getpid());

    }else{
        /* Se imprime el ID del proceso padre */
        printf("---> Proceso padre con ID %d\n", getpid());
    }

    printf("imprimiendo......\n");
    // Se realiza un ciclo de 5 iteraciones para imprimir un numero de 0 a 4
    for (int i = 0;i < 5;i++){
        /* Se imprime un    mensaje indicando que se esta en el proceso hijo */
        printf(" \t\t == %d == \n", i);
    }

    printf("FIN...........\n");

    return 0;
}