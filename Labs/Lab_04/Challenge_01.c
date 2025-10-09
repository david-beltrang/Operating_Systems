/************************************************************************************
 * Fecha: Octubre 7 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 1
*************************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (){
        printf("\n#=>Inicio del proceso main o proceso principal<=#\n\n");
        /*Se crea un proceso usando la funcion fork() que retorna el ID del proceso*/
        int procesoID = fork();

        /* Se verifica si fork() retorno un valor positivo o negativo para saber si es proceso padre o hijo */
        if(procesoID>0)
                /* Se imprime el ID del proceso padre */
                printf("\t ##==>Proceso Padre con ID %d \n", getpid());
        else if(procesoID==0){
                /*Se imprime el ID del proceso hijo*/
                printf("\t ##==>Proceso Hijo con ID %d \n", getpid());
        
            }
        else {
            /*Hubo un error al crear el proceso hijo*/
            perror("Error al crear el proceso hijo");
            exit(EXIT_FAILURE);
        }
        
        /* Se imprime un mensaje indicando que se esta en el proceso principal */
        printf(" A partir de aqui es el proceso main o proceso principal\n\n");
        return 0;
}