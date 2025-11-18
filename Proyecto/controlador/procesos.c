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

// Función simple para enviar respuesta a un agente
void enviar_respuesta(const char* pipe_agente, const char* mensaje) {
    // Abrir el pipe del agente en modo escritura
    int fd = open(pipe_agente, O_WRONLY);

    // Enviar el mensaje si el pipe se abrió correctamente
    if (fd != -1) {
        // Enviar el mensaje al agente
        write(fd, mensaje, strlen(mensaje) + 1);
        // Cerrar el pipe después de enviar el mensaje
        close(fd);
    }
}

// Procesar el avance de la hora simulada
void procesar_avance_hora() {
    // Bloquear el mutex para sincronización
    pthread_mutex_lock(&mutex);

    // Imprimir la hora actual del parque
    printf("\n╔══════════════════════════════════════╗\n");
    printf("║         HORA ACTUAL: %2d:00           ║\n", hora_actual);
    printf("╚══════════════════════════════════════╝\n");

    // Sacar las familias que deben salir en esta hora
    sacar_salientes();

    // Mostrar el estado actual del parque
    int i = idx(hora_actual);
    printf("   Personas en el parque: %d / %d\n", reservas.personas[i], aforo_max);

    // Mostrar las familias presentes
    if (strlen(reservas.familias[i]) > 0)
        printf("   Familias presentes: %s\n", reservas.familias[i]);

    hora_actual++;

    // Verificar si se alcanzó la hora final
    if (hora_actual > hora_fin) {
        terminar = 1;
        printf("\n¡Fin de la simulación!\n");
    // Ajustar la alarma para la siguiente hora
    } else {
        alarm(seg_horas);
    }

    // Desbloquear el mutex después de actualizar
    pthread_mutex_unlock(&mutex);
}
