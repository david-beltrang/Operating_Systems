# Autor: David Beltran Gomez
# Materia: Sistemas Operativos
# Makefile: Automatiza instrucciones de compilación

# Definir el compilador (Variable estándar de Make para el compilador C)
CC = gcc

# Definir los ejecutables
EJECUTABLES = progra1 progra2 progra3

# Regla por defecto: compila todos los ejecutables
all: $(EJECUTABLES)

# Reglas explícitas de compilación usando $(CC)

progra1: Challenge1.c
	$(CC) -o progra1 Challenge1.c -Wall

progra2: Challenge2.c
	$(CC) -o progra2 Challenge2.c -Wall

progra3: Challenge3.c
	$(CC) -o progra3 Challenge3.c -Wall

# Regla para limpiar los ejecutables
clean:
	rm -f $(EJECUTABLES)

.PHONY: all clean
