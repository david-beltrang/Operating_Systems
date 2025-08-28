/**************************************************************************************
 * Fecha: Agosto 27 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 2
**************************************************************************************/

//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Funcion Principal
int main() {

	//Declara un puntero 'q' que se inicializa en NULL
	char *q = NULL;

	printf("Requesting space for \"Goodbye\" \n");
	//Calcula la longitud de la cadena de caracteres y agrega uno más para caracter nulo
	q = (char *)malloc(strlen("Goodbye")+1);

	//Si malloc falla, no se pudo reservar memoria y finaliza el programa
	if (!q) {
		//Muestra en pantalla el error si falla
		perror("Failed to allocate space because");
		exit(1);
	}

	//Imprime la direccion de memoria del puntero q sin embargo no tiene
	printf("About to copy \"Goodbye\" to q at address %p\n", (void*)q);
	//Copia la cadena a la memoria que apunta q
	strcpy(q, "Goodbye");

	printf("String copied\n");
	//Imprime en pantalla la cadena que esta en q
	printf("%s \n", q);

	//Liberar memoria del apuntador
	free(q);

	return 0;
}
