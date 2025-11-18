/****************************************************************************
*                   Pontificia Universidad Javeriana                        *
*                                                                           *
*   Proyecto: Sistema de Reservas Parque Berlín - 2025-30                   * 
*   Autores: David Beltrán Gómez, Juan Felipe Gómez López, Xamuel Perez     *
*   Fecha: 11 Noviembre 2025                                                *
*   Materia: Sistemas Operativos                                            *
*   Descripción:                                                            *
*	    Implementación del Agente que envía solicitudes de reserva al       *
*       Controlador del Parque Berlín, utilizando mecanismos de             *
*       comunicación entre procesos (Pipes FIFO).                           *
*                                                                           *
*****************************************************************************/

#include "util.h"
#include "agente.h"

int main(int argc, char *argv[]) {
    // Procesamiento de argumentos
    char nombre[64] = "";
    char archivo[256] = "";
    // Pipe principal del controlador
    char pipe_principal[256] = "";
    
    int opt;
    // Leer argumentos de línea de comandos para nombre, archivo y pipe principal
    while ((opt = getopt(argc, argv, "s:a:p:")) != -1) {
        // Según el argumento, asignar el valor correspondiente
        switch (opt) {
            case 's': strncpy(nombre, optarg, sizeof(nombre)-1); break;
            case 'a': strncpy(archivo, optarg, sizeof(archivo)-1); break;
            case 'p': strncpy(pipe_principal, optarg, sizeof(pipe_principal)-1); break;
        }
    }

    // Verificar que se proporcionaron todos los argumentos necesarios
    if(nombre[0]==0 || archivo[0]==0 || pipe_principal[0]==0){
        fprintf(stderr, "Uso: %s -s <nombre> -a <archivo.csv> -p <pipe>\n", argv[0]);
        return 1;
    }

    return procesar_agente(nombre, archivo, pipe_principal);
}
