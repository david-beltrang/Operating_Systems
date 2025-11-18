###########################################################################
#					Pontificia Universidad Javeriana
# Autores: David Beltran Gomez, Xamuel Pérez Hernández, Juan Gomez Lopez
# Materia: Sistemas Operativos
# Proyecto: Sistema de Reservas Parque Berlín - 2025-30
# Fichero: Automaticación Compilación
###########################################################################

GCC   = gcc
FLAGS = -pthread -Wall

AGENTE      = agente
CONTROLADOR = controlador

AGENTE_SRC = agenteFicheros/agente.c \
             agenteFicheros/mainAgente.c

CONTROL_SRC = controladorFicheros/hilo.c \
              controladorFicheros/manejadores.c \
              controladorFicheros/procesos.c \
              controladorFicheros/reporte.c \
              controladorFicheros/reservas.c \
              controladorFicheros/mainControlador.c

all: $(AGENTE) $(CONTROLADOR)

$(AGENTE):
	$(GCC) $(AGENTE_SRC) -o $@ $(FLAGS)

$(CONTROLADOR):
	$(GCC) $(CONTROL_SRC) -o $@ $(FLAGS)

clean:
	$(RM) $(AGENTE) $(CONTROLADOR)