###########################################################################
#					Pontificia Universidad Javeriana
# Autores: David Beltran Gomez, Xamuel Pérez Hernández, Juan Gomez Lopez
# Materia: Sistemas Operativos
# Proyecto: Sistema de Reservas Parque Berlín - 2025-30
# Fichero: Automaticación Compilación
###########################################################################

GCC   = gcc
FLAGS = -pthread -lrt -Wall

PROGRAMAS = controlador agente

all: $(PROGRAMAS)

controlador:
	$(GCC) controlador/*.c -o $@ $(FLAGS)

agente:
	$(GCC) agente/*.c -o $@ $(FLAGS)

clean:
	$(RM) $(PROGRAMAS)
