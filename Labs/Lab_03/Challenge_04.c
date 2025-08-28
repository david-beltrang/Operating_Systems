/**************************************************************************************
 * Fecha: Agosto 27 del 2025
 * Autor: David Beltrán Gómez
 * Materia: Sistemas Operativos
 * Tema: Challenge 4
**************************************************************************************/

//Librerias
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Función principal
int main() {
	//Declara 3 variables y un apuntador de tipo entero
	int n, i, *ptr, sum = 0;

	printf("Enter number of elements: ");
	//Guarda lo que digiten en pantalla en la variabe n
	scanf("%d", &n);

	//Inicializa el apuntador a un bloque de n numeros enteros
	ptr = (int*) calloc(n, sizeof(int));

	//Verifica si el apuntador es Nulo
	if(ptr == NULL) {
		printf("Error! memory not allocated.");
		exit(0);
	}

	//Recorre el bloque de enteros
	for(i = 0; i < n; ++i) {
		//Solicita el número a ingresar
		printf("Enter elements: ");
		//Guarda el valor ingresado en la poscion i del bloque de enteros
		scanf("%d", ptr + i);
		//Acumula todos los números en un sumador
		sum += *(ptr + i);
	}

	//Imprime en pantalla la suma total de todos los números
	printf("Sum = %d\n", sum);

	//Liberar memoria
	free(ptr);

	return 0;
}
