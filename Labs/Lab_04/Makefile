  GNU nano 6.2                                                      Makefile                                                                # Fecha: 7 Octubre del 2025
# Autor: David Beltran Gomez
# Materia: Sistemas Operativos
# Makefile: Automatiza instrucciones de compilación

# Nombre del compilador
CC = gcc

# Definir los ejecutables
EJECUTABLES = progra1 progra2 progra3

# Regla por defecto: compila todos los ejecutables
all: $(EJECUTABLES)

# Reglas explícitas de compilación usando $(CC)

progra1: Challenge_01.c
        $(CC) -o progra1 Challenge_01.c -Wall

progra2: Challenge_02.c
        $(CC) -o progra2 Challenge_02.c -Wall

progra3: Challenge_03.c
        $(CC) -o progra3 Challenge_03.c -Wall

# Regla para limpiar los ejecutables
clean:
        rm -f $(EJECUTABLES)

.PHONY: all clean