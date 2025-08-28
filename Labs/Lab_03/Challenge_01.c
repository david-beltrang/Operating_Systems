/**************************************************************************************
 * Fecha: Agosto 27 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 1
**************************************************************************************/

// Librerias
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Funcion Principal
int main() {
	// Reserva memoria dinámica y la asigna a un nuevo apuntador de tipo char
	char *p = malloc(60 * sizeof(char));
	// Reserva memoria dinámica y la asigna a un nuevo apuntador de tipo char
	char *q = malloc(10 * sizeof(char));
	//Imprime la direccion de memoria del apuntador P
	printf("Address of p = %p\n", (void *)p);


	strcpy(p, "Hello, I'm the best in Operating Systems!!!");
	//Copia esa cadena de texto en la memoria apuntada por el apuntador P
	printf("%s\n", p);

	printf("About to copy \"Goodbye\" to q\n");
	//Copia esa cadena de texto en la memoria apuntada por el apuntador Q
	strcpy(q, "Goodbye");

	printf("String copied\n");
	//Imprime la cadena de caracteres a la que apunta P
	printf("%s\n", q);

	// Liberar memoria
	free(p);
	free(q);

	return 0;
}
