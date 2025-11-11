/********************************************************
*           Pontificia Universidad Javeriana            *
*                                                       *
*   Autor: David Esteban Beltrán Gómez                  *
*   Fecha: 11 Noviembre 2025                            *
*   Materia: Sistemas Operativos                        *
*   Tema: Sistemas de Ficheros                          *
*   Descripción:                                        *
*	-Programa en C que lea del teclado el nombre        *
*       de un directorio y muestre el nombre y tamaño   *
*       de todos los ficheros regulares que contiene.   *
*********************************************************/

#include <sys/types.h>      // Interfaz necesaria para los tipos de datos "stat" y "mode_t"
#include <sys/stat.h>       // Interfaz necesaria para la estructura "stat" y la función "stat()""
#include <stdio.h>          // Interfaz necesaria para funciones de Input/Output
#include <unistd.h>         // Interfaz necesaria para los llamados al sistema como "read", "close", "opendir"
#include <string.h>         // Interfaz necesaria para las funciones de cadenas de texto como "strcpy" y "strcat"
#include <dirent.h>         // Interfaz necesaria para usar los directorios e implementar "opendir", "readdir" y "closedir"

int main() {
    DIR *d;                   // Puntero a un directorio que se abrirá
    char nomdir[90], nomfich[90];  // Arrays para almacenar el nombre del directorio y del archivo
    struct stat datos;        // Estructura para almacenar la información del fichero
    struct dirent *direc;     // Estructura que representa una entrada de directorio 

    printf("Se dispone del directorio 'Patito' para pruebas.\n");
    printf("Introduzca el Nombre de un Directorio: ");
    fgets(nomdir, sizeof(nomdir), stdin);  // Lee el nombre del directorio que ponga el usario
    nomdir[strlen(nomdir) - 1] = '\0';     // Elimina el carácter \n de la cadena

    // Intenta abrir el directorio
    if ((d = opendir(nomdir)) == NULL){
        // Si no se puede abre el directorio, muestra un mensaje de error y termina el programa
        printf("El directorio no existe\n");
        return -1;
    }

    // Lee los ficheros y/o subdirectorios dentro del directorio
    while ((direc = readdir(d)) != NULL){
        // Construye la ruta completa del archivo concatenando el directorio y el nombre del archivo
        strcpy(nomfich, nomdir);               // Copia el nombre del directorio a "nomfich"
        strcat(nomfich, "/");                  // Añade una barra '/' para separar el directorio del archivo
        strcat(nomfich, direc->d_name);        // Añade el nombre del archivo/subdirectorio a la ruta completa

        stat(nomfich, &datos);                 // Obtiene la información del archivo

        // Verifica si losdatos que contiene la estructura son validos
        if (S_ISREG(datos.st_mode)) {
            // Si es un archivo regular, muestra su nombre y tamaño
            printf("Nombre: %s\t| Tamaño: %ld\n", direc->d_name, datos.st_size);
        }
    }

    // Cierra el directorio después de procesarlo
    closedir(d);
    return 0;  // Termina el programa con éxito
}