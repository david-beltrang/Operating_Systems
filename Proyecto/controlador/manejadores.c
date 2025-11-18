/****************************************************************************
*                   Pontificia Universidad Javeriana                        *
*                                                                           *
*   Proyecto: Sistema de Reservas Parque Berlín - 2025-30                   *
*   Autores: David Beltrán Gómez, Juan Felipe Gómez López, Xamuel Perez     *
*   Fecha: 11 Noviembre 2025                                                *
*   Materia: Sistemas Operativos                                            *
*****************************************************************************/

#include "shared.h"
#include "manejadores.h"

// Manejador de la señal SIGALRM para avanzar la hora
void manejador_alarma(int sig) {
    // Ignorar el argumento
    (void)sig;
    // Marcar que la alarma está pendiente
    alarma_pendiente = 1;
}
