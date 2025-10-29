/************************************************************************************
 * Fecha: Octubre 28 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: POSIX para Hilos recurrentes
 * Descripción: Leer desde un fichero y busqueda praralela del valor máximo.
*************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct argHilos{
        int inicio;     // Indice inicial del subarray que procesa el hilo
        int fin;        // Indice final del subarray que procesa el hilo
        int *vector;    // Puntero al array completo leído desde fichero
        int maxparcial; // Lugar donde el hilo debe guardar su máximo local
};

typedef struct argHilos param_H;

void *buscarMax(void *parametro){
        param_H *argumentos = (param_H *)parametro;	// Casteo de void* a struct argHilos*
        argumentos->maxparcial = argumentos->vector[argumentos->inicio];	// Inicializar máximo parcial
        for(int i=0; i<argumentos->fin; i++){
                if(argumentos->vector[i] > argumentos->maxparcial) // Actualizar máximo parcial si se encuentra un valor mayor
                        argumentos->maxparcial = argumentos->vector[i]; // Actualización del máximo parcial
        }
        pthread_exit(0); // Terminar el hilo
        return NULL;     // Retorno redundante
}

int main(int argc, char *argv[]) {
        FILE *fichero;
        int n, nhilos, i;
        int *vec;
        int ret, maximo;

        /* Comprobar número de argumentos: se espera ./prog fichero nhilos */
        if (argc!=3) {
                fprintf(stderr, "Error en número de argumentos \n");
                exit(-1);
        }
        fichero = fopen(argv[1], "r"); // Abrir fichero de entrada (argv[1])
        if (fichero == NULL) {
                perror("No se puede abrir fichero");
                exit(-2);
        }
        ret = fscanf(fichero, "%d", &n); // Leer cantidad de elementos n
        if (ret !=1) {
                fprintf(stderr, "No se puede leer tamaño\n");
                exit(-3);
        }
        nhilos = atoi(argv[2]); // Número de hilos solicitado (no validado aquí)
        vec = malloc(sizeof(int) * n); // Reservar memoria para el vector
        for (i=0;i!=n;++i) {
                ret = fscanf(fichero, "%d", &vec[i]);
                if (ret !=1) {
                        fprintf(stderr, "No se puede leer elemento nro %d\n", i);
                        fclose(fichero);
                        free(vec);
                }
        }
        maximo = buscarMax(vec); // Llamar a función que debe crear hilos y devolver máximo
        printf("Máximo: %d\n", maximo); // Imprimir resultado
        fclose(fichero); // Cerrar fichero
        free(vec);       // Liberar memoria
        return 0;
}
