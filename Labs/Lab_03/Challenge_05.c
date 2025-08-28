/**************************************************************************************
 * Fecha: Agosto 27 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 5
**************************************************************************************/

//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Función principal
int main() {
	//Declara 3 variables y un apuntador de tipo Entero
	int *ptr, i , n1, n2;

	//Solicita el tamaño del bloque de enteros
	printf("Enter size: ");
	scanf("%d", &n1);

	//Reserva memoria para un bloque de n1 números enteros
	ptr = (int*) malloc(n1 * sizeof(int));

	printf("\nAddresses of previously allocated memory: ");
	//Recorre el bloque de enteros
	for(i = 0; i < n1; ++i)
		//Imprime la direccionde memoria del apuntador
		printf("\np = %p\n", ptr+i);

	//Solicita un nuevo tamaño para el bloque de enteros
	printf("\n Enter the new size: ");
	scanf("%d", &n2);

	//Redimensiona el bloque de enteros que habia inicialmente
	ptr = realloc(ptr, n2 * sizeof(int));

	printf("\nAddresses of newly allocated memory: ");
	//Imprime en pantalla las nuevas direcciones de memoria
	for(i = 0; i < n2; ++i)
		printf("\np = %p\n", ptr+i);

	//Liberar memoria
	free(ptr);

	return 0;
}
