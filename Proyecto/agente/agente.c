/****************************************************************************
*                   Pontificia Universidad Javeriana                        *
*                                                                           *
*   Proyecto: Sistema de Reservas Parque Berlín - 2025-30                   *
*   Autores: David Beltrán Gómez, Juan Felipe Gómez López, Xamuel Perez     *
*   Fecha: 11 Noviembre 2025                                                *
*   Materia: Sistemas Operativos                                            *
*****************************************************************************/

#include "shared.h"
#include "agente.h"

int procesar_agente(const char *nombre_arg, const char *archivo_arg, const char *pipe_principal_arg) {

    // Procesamiento de argumentos
    char nombre[64] = "";
    char archivo[256] = "";
    // Pipe principal del controlador
    char pipe_principal[256] = "";

    // Copiar argumentos recibidos
    strncpy(nombre, nombre_arg, sizeof(nombre)-1);
    strncpy(archivo, archivo_arg, sizeof(archivo)-1);
    strncpy(pipe_principal, pipe_principal_arg, sizeof(pipe_principal)-1);

    // 1. Crear pipe personal del agente
    char pipe_personal[256];
    // Utilizar el nombre del agente para crear un pipe único
    snprintf(pipe_personal, sizeof(pipe_personal), "/tmp/pipe_%s", nombre);
    // Unlink para eliminar cualquier pipe existente con el mismo nombre
    unlink(pipe_personal);

    // Crear el FIFO (pipe nombrado)
    if (mkfifo(pipe_personal, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    printf("[AGENTE %s] Iniciando... pipe personal: %s\n", nombre, pipe_personal);

    // 2. Registrarse en el controlador
    int fd = open(pipe_principal, O_WRONLY);
    // Comprobar si se pudo abrir el pipe principal
    if (fd == -1) {
        perror("open principal"); return 1;
    }

    // Buffer para el mensaje de registro
    char mensaje[BUFFER];
    // Formatear el mensaje de registro con el nombre del agente y su pipe personal
    snprintf(mensaje, sizeof(mensaje), "REGISTRO|%s|%s", nombre, pipe_personal);
    // Enviar el mensaje al controlador
    write(fd, mensaje, strlen(mensaje)+1);
    // Cerrar el pipe después de enviar el mensaje
    close(fd);

    // 3. Esperar hora actual
    int fd_resp = open(pipe_personal, O_RDONLY);
    // Comprobar si se pudo abrir el pipe personal
    if (fd_resp == -1) {
        perror("open personal"); return 1;
    }

    // Buffer para la respuesta del controlador
    char resp[BUFFER];
    // Leer la respuesta que contiene la hora actual del parque
    read(fd_resp, resp, BUFFER);
    int hora_actual = 0;
    // Extraer la hora actual del mensaje recibido
    sscanf(resp, "HORA_ACTUAL|%d", &hora_actual);
    // Mostrar la hora actual recibida
    printf("[AGENTE %s] Hora actual del parque: %d:00\n", nombre, hora_actual);

    // 4. Procesar archivo CSV
    FILE *f = fopen(archivo, "r");
    // Comprobar si se pudo abrir el archivo CSV
    if (!f) {
        perror("fopen csv"); return 1;
    }

    char linea[256];

    // Leer cada línea del archivo CSV y procesar las reservas
    while (fgets(linea, sizeof(linea), f)) {
        char familia[100];
        int hora_sol, personas;

        // Extraer los datos de la línea (familia, hora solicitada, número de personas)
        if (sscanf(linea, "%99[^,],%d,%d", familia, &hora_sol, &personas) != 3)
            continue;

        // Omitir reservas para horas pasadas
        if (hora_sol < hora_actual) {
            printf("[AGENTE %s] Omitiendo reserva pasada: %s (%d:00)\n", nombre, familia, hora_sol);
            continue;
        }

        // Mostrar la solicitud de reserva
        printf("[AGENTE %s] → Reserva: %s, %d:00, %d personas\n", nombre, familia, hora_sol, personas);

        // Enviar solicitud al controlador
        fd = open(pipe_principal, O_WRONLY);
        // Formatear el mensaje de solicitud
        snprintf(mensaje, sizeof(mensaje), "SOLICITUD|%s|%s|%d|%d", nombre, familia, hora_sol, personas);
        // Enviar el mensaje al controlador
        write(fd, mensaje, strlen(mensaje)+1);
        // Cerrar el pipe después de enviar la solicitud
        close(fd);

        // Esperar la respuesta del controlador
        read(fd_resp, resp, BUFFER);
        printf("[AGENTE %s] ← %s\n", nombre, resp);

        sleep(2);
    }

    // 5. Finalizar agente
    fclose(f);
    // Cerrar el pipe de respuesta
    close(fd_resp);
    // Unlink para eliminar el pipe personal del agente
    unlink(pipe_personal);
    printf("Agente %s termina.\n", nombre);
    return 0;
}
