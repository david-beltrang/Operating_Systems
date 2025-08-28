/**************************************************************************************
 * Fecha: Agosto 27 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 3
**************************************************************************************/

//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Función principal
int main() {
	//Crea un puntero de tipo entero sin inicializar
	int *ptr;

	//Reserva memoria dinamica para un bloque de 15 enteros
	ptr = malloc(15 * sizeof(*ptr));
	//Verifica si el apuntador no es NULL
	if (ptr != NULL) {
		//Guarda el valor de 480 en la Sexta posición del bloque de enteros
		*(ptr + 5) = 480;
		//Imprime en pantalla el valor en la Sexta posición
		printf("Value of the 6th Integrer is %d\n",*(ptr+5));
	}

	//Liberar memoria
	free(ptr);

	return 0;
}

