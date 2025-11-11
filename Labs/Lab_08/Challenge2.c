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

#include <string.h>         // Interfaz necesaria para trabajar con cadenas de texto, como "strcpy" y "strcat"
#include <time.h>           // Interfaz necesaria para trabajar con fechas y horas
#include <sys/types.h>      // Interfaz necesaria para los tipos de datos "stat" y "mode_t"
#include <sys/stat.h>       // Interfaz necesaria para la estructura "stat" y la función "stat()""
#include <stdio.h>          // Interfaz necesaria para funciones de Input/Output
#include <unistd.h>         // Interfaz necesaria para los llamados al sistema como "read", "close", "opendir"
#include <string.h>         // Interfaz necesaria para las funciones de cadenas de texto como "strcpy" y "strcat"
#include <dirent.h>         // Interfaz necesaria para usar los directorios e implementar "opendir", "readdir" y "closedir"

int main() {
    int er;                       // Variable para el error en caso de que ocurra
    char nomdir[100], nomfich[100], resp[30];  // Variables para almacenar nombres de directorios y archivos
    struct stat atr;               // Estructura para almacenar atributos de un archivo o directorio
    DIR *d;                        // Puntero a un directorio
    struct dirent *rd1;            // Estructura para una entrada de directorio
    time_t fecha;                  // Variable para almacenar la fecha y hora actual
    printf("Se dispone del directorio 'Patito' para pruebas.\n");
    printf("Nombre directorio\n");
    fgets(nomdir, sizeof(nomdir), stdin);  // Lee el nombre del directorio que ingresa el usuario
    
    // Elimina el carácter '\n' que se agrega al final del nombre del directorio por fgets 
    nomdir[strlen(nomdir) -1] = '\0';  

    fecha = time(&fecha);  // Obtiene la hora actual

    // Intenta abrir el directorio especificado por el usuario
    if ((d = opendir(nomdir)) == NULL) {
        // Si no se puede abrir el directorio, muestra un mensaje de error y termina el programa
        printf("No existe ese directorio \n");
        return -1;
    } else {
        // Lee los ficheros y/o subdirectorios dentro del directorio
        while ((rd1 = readdir(d)) != NULL) {
            // Omite las entradas especiales "." y ".."
            if ((strcmp(rd1 -> d_name, ".") != 0) && (strcmp(rd1 -> d_name, "..") != 0)) {
                // Construye la ruta completa del archivo o directorio
                strcpy(nomfich, nomdir);               // Copia el nombre del directorio a "nomfich"
                strcat(nomfich, "/");                  // Añade una barra '/' para separar el directorio del archivo
                strcat(nomfich, rd1 -> d_name);        // Añade el nombre de la entrada a la ruta completa

                // Imprime el nombre del archivo o subdirectorio
                printf("fichero :%s:", nomfich);

                // Obtiene los atributos del archivo usando la función 'stat'
                er = stat(nomfich, &atr);

                // Imprime los permisos que tiene el fichero
                printf("modo :%#o:", atr.st_mode);

                // Verifica si el archivo tiene permiso de lectura para el propietario
                if ((atr.st_mode & 0400) != 0) 
                    printf(" permiso R para propietario\n");
                else
                    printf(" No permiso R para propietario\n");

                // Verifica si la entrada es un directorio
                if (S_ISDIR(atr.st_mode)) 
                    printf(" Es un directorio \n");

                // Verifica si la entrada es un archivo regular
                if (S_ISREG(atr.st_mode)) {
                    /* Verifica si el archivo ha sido modificado en los últimos 10 días */
                    if ((fecha - 10 * 24 * 60 * 60) < atr.st_mtime) {
                        // Si el archivo fue modificado en los últimos 10 días, imprime la información
                        printf("FICHERO:%s: fecha acceso %s, en sgdos %ld\n", rd1 -> d_name,
                               ctime(&atr.st_mtime), atr.st_mtime);
                    }
                }
            }
        }
        
        // Cierra el directorio después de procesarlo
        closedir(d);
    }

    return 0;  // Termina el programa con éxito
}
/*CONCULSIONES:
    Aprendido a manejar directorios y archivos en C utilizando las funciones de la biblioteca estándar. 
    Hemos visto cómo abrir un directorio, leer sus entradas y obtener información detallada sobre cada archivo, como sus permisos y fechas de modificación. 
    Además, hemos aprendido a filtrar archivos basándonos en criterios específicos, como la fecha de modificación. 
    Este conocimiento es fundamental para trabajar con sistemas de archivos en aplicaciones de C.
*/