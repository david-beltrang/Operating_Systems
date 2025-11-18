#ifndef RESERVAS_H
#define RESERVAS_H

int idx(int hora);
int verificar_disponibilidad(int hora, int personas);
int buscar_alternativa(int personas, int desde);
void agregar_reserva(int hora, int personas, const char* familia);
void sacar_salientes();

#endif
