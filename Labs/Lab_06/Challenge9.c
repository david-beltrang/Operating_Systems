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
        param_H *argumentos = (param_H *)parametro;
        argumentos->maxparcial = argumentos->vector[argumentos->inicio];
        for(int i = argumentos->inicio; i < argumentos->fin; i++){
                if(argumentos->vector[i] > argumentos->maxparcial)
                        argumentos->maxparcial = argumentos->vector[i];
        }
        pthread_exit(0);
        return NULL;
}

int main(int argc, char *argv[]) {
        FILE *fichero;
        int n, nhilos, i;
        int *vec;
        int ret;

        if (argc!=3) {
                fprintf(stderr, "Error en numero de argumentos\n");
                exit(-1);
        }
        fichero = fopen(argv[1], "r");
        if (fichero == NULL) {
                perror("No se puede abrir fichero");
                exit(-2);
        }
        ret = fscanf(fichero, "%d", &n);
        if (ret !=1) {
                fprintf(stderr, "No se puede leer tamano\n");
                exit(-3);
        }
        nhilos = atoi(argv[2]);
        if (nhilos < 1) nhilos = 1;
        if (nhilos > n) nhilos = n;

        vec = malloc(sizeof(int) * n);
        for (i=0;i!=n;++i) {
                ret = fscanf(fichero, "%d", &vec[i]);
                if (ret !=1) {
                        fprintf(stderr, "No se puede leer elemento nro %d\n", i);
                        fclose(fichero);
                        free(vec);
                        exit(-4);
                }
        }
        fclose(fichero);

        pthread_t *hilos = malloc(nhilos * sizeof(pthread_t));
        param_H *args = malloc(nhilos * sizeof(param_H));
        int chunk = n / nhilos;

        for (i = 0; i < nhilos; i++) {
                args[i].inicio = i * chunk;
                args[i].fin = (i == nhilos - 1) ? n : (i + 1) * chunk;
                args[i].vector = vec;
                args[i].maxparcial = 0;
                pthread_create(&hilos[i], NULL, buscarMax, &args[i]);
        }

        int maximo = vec[0];
        for (i = 0; i < nhilos; i++) {
                pthread_join(hilos[i], NULL);
                if (args[i].maxparcial > maximo)
                        maximo = args[i].maxparcial;
        }

        printf("Maximo: %d\n", maximo);
        free(vec);
        free(hilos);
        free(args);
        return 0;
}
