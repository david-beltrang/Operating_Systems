#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>      // Interfaz estándar de entrada y salida
#include <stdlib.h>     // Funciones de utilidad general
#include <string.h>     // Manipulación de cadenas
#include <errno.h>      // Manejo de errores
#include <unistd.h>     // Funciones POSIX (como read, write, close)
#include <fcntl.h>      // Operaciones de control de archivos
#include <sys/stat.h>   // Operaciones de estado de archivos
#include <signal.h>     // Manejo de señales
#include <pthread.h>    // Hilos POSIX

#define MAX_HORAS    13     // De 7:00 a 19:00 (13 horas)
#define MAX_BUFFER   1024   // Tamaño máximo para buffers de mensajes

// Estructura para almacenar las reservas
typedef struct {
    int personas[MAX_HORAS];    // Personas reservadas por hora
    char familias[MAX_HORAS][MAX_BUFFER];   // Nombres de familias por hora
} Reservas;

// Estructura para estadísticas de reservas
typedef struct {
    int aceptadas;      // Contador de reservas aceptadas
    int reprogramadas;  // Contador de reservas reprogramadas
    int negadas;        // Contador de reservas negadas
} Estadisticas;

extern int hora_actual, hora_ini, hora_fin, seg_horas, aforo_max;
extern char pipe_principal[256];
extern Reservas reservas;
extern Estadisticas stats;
extern pthread_mutex_t mutex;
extern volatile sig_atomic_t alarma_pendiente;
extern volatile sig_atomic_t terminar;

#endif // SHARED_H