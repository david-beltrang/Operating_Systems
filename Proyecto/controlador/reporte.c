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
#include "reporte.h"

//Generar reporte final en archivo .csv
void generar_reporte() {
    // Abrir el archivo de reporte en modo escritura
    FILE *f = fopen("reporte_final.csv", "w");
    // Comprobar si se pudo abrir el archivo
    if (!f) {
        perror("fopen reporte");
        return;
    }

    fprintf(f, "Hora,Personas,Familias\n");

    // Escribir los datos de reservas por hora
    for (int h = hora_ini; h <= hora_fin; h++) {
        int i = idx(h);
        fprintf(f, "%d:00,%d,%s\n", h, reservas.personas[i],
                strlen(reservas.familias[i]) > 0 ? reservas.familias[i] : "Ninguna");
    }

    fprintf(f, "\nEstadísticas:\n");
    fprintf(f, "Aceptadas,%d\n", stats.aceptadas);
    fprintf(f, "Reprogramadas,%d\n", stats.reprogramadas);
    fprintf(f, "Negadas,%d\n", stats.negadas);

    // Cerrar el archivo de reporte
    fclose(f);

    printf("\n[CONTROLADOR] Reporte generado: reporte_final.csv\n");
}
