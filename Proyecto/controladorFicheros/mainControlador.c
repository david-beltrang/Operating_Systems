/****************************************************************************
*                   Pontificia Universidad Javeriana                        *
*                                                                           *
*   Proyecto: Sistema de Reservas Parque Berlín - 2025-30                   *
*   Autores: David Beltrán Gómez, Juan Felipe Gómez López, Xamuel Perez     *
*   Fecha: 11 Noviembre 2025                                                *
*   Materia: Sistemas Operativos                                            *
*   Descripción:                                                            *
*       Implementación completa del Controlador de Reservas del             *
*       Parque Berlín, utilizando mecanismos de comunicación                *
*       entre procesos (Pipes FIFO), manejo de señales POSIX                *
*       (SIGALRM), concurrencia mediante hilos POSIX, y                     *
*       sincronización con mutex.                                           *
*                                                                           *
*   El Controlador gestiona:                                                *
*     - Registro de Agentes                                                 *
*     - Recepción concurrente de solicitudes de reserva                     *
*     - Validación de aforo disponible por hora                             *
*     - Asignación, reprogramación o negación de reservas                   *
*     - Avance automático de la hora simulada                               *
*     - Control de ocupación por hora (dos horas por reserva)               *
*     - Reporte estadístico final de toda la simulación                     *
*****************************************************************************/


#include "shared.h"
#include "manejadores.h"
#include "hilo.h"
#include "reporte.h"
#include "procesos.h"

// Variables globales
int hora_actual = 7, hora_ini = 7, hora_fin = 19;
int seg_horas = 10, aforo_max = 100;
char pipe_principal[256];
Reservas reservas;
Estadisticas stats = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
volatile sig_atomic_t alarma_pendiente = 0;
volatile sig_atomic_t terminar = 0;

int main(int argc, char* argv[]) {

    // Procesamiento inicial
    snprintf(pipe_principal, sizeof(pipe_principal), "/tmp/pipe_parque");
    unlink(pipe_principal);

    if (mkfifo(pipe_principal, 0666) == -1) {
        perror("mkfifo principal");
        return 1;
    }

    printf("[CONTROLADOR] Iniciando simulación...\n");

    // Instalar manejador de SIGALRM
    signal(SIGALRM, manejador_alarma);

    // Crear hilo para atender agentes
    pthread_t th;
    pthread_create(&th, NULL, hilo_reservas, NULL);

    // Activar la alarma
    alarm(seg_horas);

    // Bucle principal de avance de horas
    while (!terminar) {

        if (alarma_pendiente) {
            alarma_pendiente = 0;
            procesar_avance_hora();
        }

        usleep(200000); // 0.2s
    }

    pthread_join(th, NULL);

    // Generar reporte final
    generar_reporte();

    unlink(pipe_principal);
    printf("[CONTROLADOR] Finalizado.\n");

    return 0;
}
