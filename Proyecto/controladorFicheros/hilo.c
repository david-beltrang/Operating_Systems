/****************************************************************************
*                   Pontificia Universidad Javeriana                        *
*                                                                           *
*   Proyecto: Sistema de Reservas Parque Berlín - 2025-30                   *
*   Autores: David Beltrán Gómez, Juan Felipe Gómez López, Xamuel Perez     *
*   Fecha: 11 Noviembre 2025                                                *
*   Materia: Sistemas Operativos                                            *
*****************************************************************************/

#include "shared.h"
#include "reservas.h"
#include "procesos.h"
#include "hilo.h"

void* hilo_reservas(void* arg) {
    (void)arg;  // Evitar warning por parámetro no usado

    char buffer[MAX_BUFFER];
    char nombre[64], familia[128], pipe_agente[256];
    int hora_sol, personas;

    // Abrir el pipe principal en modo lectura
    int fd = open(pipe_principal, O_RDONLY);
    if (fd == -1) {
        perror("open pipe principal");
        return NULL;
    }

    // Leer constantemente solicitudes de agentes
    while (!terminar) {

        // Leer un mensaje del pipe
        int n = read(fd, buffer, sizeof(buffer));
        if (n <= 0) continue;

        // Intentar interpretar como registro
        if (sscanf(buffer, "REGISTRO|%63[^|]|%255[^|]", nombre, pipe_agente) == 2) {
            printf("[CONTROLADOR] Registrado agente %s, pipe: %s\n", nombre, pipe_agente);

            // Enviar hora actual al agente
            char msg[64];
            snprintf(msg, sizeof(msg), "HORA_ACTUAL|%d", hora_actual);
            enviar_respuesta(pipe_agente, msg);
            continue;
        }

        // Intentar interpretar como solicitud de reserva
        if (sscanf(buffer, "SOLICITUD|%63[^|]|%127[^|]|%d|%d",
                   nombre, familia, &hora_sol, &personas) == 4) {

            pthread_mutex_lock(&mutex);

            printf("\n[CONTROLADOR] Solicitud de %s (%s): %d personas a las %d:00\n",
                   nombre, familia, personas, hora_sol);

            char msg[MAX_BUFFER];

            // 1) Verificar si hay disponibilidad en la hora solicitada
            if (verificar_disponibilidad(hora_sol, personas)) {
                agregar_reserva(hora_sol, personas, familia);
                stats.aceptadas++;

                snprintf(msg, sizeof(msg),
                         "ACEPTADA|%s|%d:00", familia, hora_sol);

                printf("   → ACEPTADA\n");

            } else {
                // 2) Buscar hora alternativa
                int alt = buscar_alternativa(personas, hora_sol);

                if (alt != -1) {
                    agregar_reserva(alt, personas, familia);
                    stats.reprogramadas++;

                    snprintf(msg, sizeof(msg),
                             "REPROGRAMADA|%s|%d:00", familia, alt);

                    printf("   → REPROGRAMADA a las %d:00\n", alt);

                } else {
                    // 3) Negada
                    stats.negadas++;

                    snprintf(msg, sizeof(msg),
                             "NEGADA|%s|SIN ESPACIO", familia);

                    printf("   → NEGADA (sin espacio)\n");
                }
            }

            pthread_mutex_unlock(&mutex);

            // Enviar la respuesta al agente
            enviar_respuesta(pipe_agente, msg);

            continue;
        }
    }

    close(fd);
    return NULL;
}
