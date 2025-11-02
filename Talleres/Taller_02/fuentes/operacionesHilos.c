#include <pthread.h>
#include <stdlib.h>
#include "operacionesHilos.h"
#include "operacionesMatrices.h"

pthread_mutex_t MM_mutex;

struct parametros{
    int nH;
    int idH;
    int N;
};

void *multiMatrix(void *variables){
    struct parametros *data = (struct parametros *)variables;
    int idH = data->idH;
    int nH = data->nH;
    int D = data->N;
    int filaI = (D/nH)*idH;
    int filaF = (D/nH)*(idH+1);
    double Suma, *pA, *pB;

    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
            pA = matrixA + i*D; 
            pB = matrixB + j;
            Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB+=D){
                Suma += *pA * *pB;
            }
            matrixC[i*D+j] = Suma;
        }
    }

    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);
    pthread_exit(NULL);
}
