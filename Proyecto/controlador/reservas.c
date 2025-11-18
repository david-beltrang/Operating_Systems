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

// Convertir hora real (7-19) a índice del array (0-12)
int idx(int hora) { return hora - 7; }

// Verificar si hay disponibilidad para una reserva en una hora dada
int verificar_disponibilidad(int hora, int personas) {
    // Verificar que la hora esté dentro del rango permitido
    if (hora + 1 > hora_fin) 
        return 0;
    // Obtener el índice correspondiente en el array
    int i = idx(hora);
    // Verificar si la suma de personas no excede el aforo máximo
    return (reservas.personas[i] + personas <= aforo_max &&
            reservas.personas[i + 1] + personas <= aforo_max);
}

// Buscar una hora alternativa con disponibilidad
int buscar_alternativa(int personas, int desde) {
    int ultima = hora_fin - 1;

    // Verificar horas desde 'desde' hasta el final del día
    for (int h = desde; h <= ultima; h++)
        if (verificar_disponibilidad(h, personas)) return h;
    
    // Verificar horas desde el inicio del día hasta 'desde'
    for (int h = hora_ini; h < desde && h <= ultima; h++)
        if (verificar_disponibilidad(h, personas)) return h;
    
    // No se encontró alternativa
    return -1;
}

// Agregar una reserva en una hora específica
void agregar_reserva(int hora, int personas, const char* familia) {
    int i = idx(hora);
    // Actualizar el conteo de personas para las dos horas de la reserva
    reservas.personas[i] += personas;
    // La reserva ocupa dos horas consecutivas
    reservas.personas[i + 1] += personas;

    char temp[128];
    // Agregar el nombre de la familia al registro de familias para ambas horas
    snprintf(temp, sizeof(temp), "%s(%d) ", familia, personas);
    // Agregar al string de familias, asegurando no exceder el buffer
    strncat(reservas.familias[i], temp, MAX_BUFFER - strlen(reservas.familias[i]) - 1);
    // Para la segunda hora de la reserva
    strncat(reservas.familias[i + 1], temp, MAX_BUFFER - strlen(reservas.familias[i + 1]) - 1);
}

// Procesar las salidas de las familias que cumplen su tiempo de reserva
void sacar_salientes() {
    // Las familias que entraron a la hora_actual - 2 deben salir
    if (hora_actual < hora_ini + 2)
        return;
    int hora_salida = hora_actual - 2;
    int i = idx(hora_salida);

    // Verificar si el índice es válido
    if (i < 0 || i >= MAX_HORAS)
        return;

    // Si hay personas que deben salir a esta hora
    if (reservas.personas[i] > 0) {
        printf("   → Salen las familias que entraron a las %d:00 (%d personas)\n",
               hora_salida, reservas.personas[i]);
    
        // Resetear las reservas para esa hora
        reservas.personas[i] = 0;
        reservas.personas[i + 1] = 0;
        reservas.familias[i][0] = '\0';
        reservas.familias[i + 1][0] = '\0';
    }
}
