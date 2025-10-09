/*************************************************************************************
 * Fecha: Agosto 12 del 2025                                                         *
 * Autor: David Beltrán Gómez                                                        *
 * Materia: Sistemas Operativos                                                      *
 * Tema: Generación de programa pricipal para la Multiplicación de Matrices          *
*************************************************************************************/

#ifndef __MODULO_H__ 
#define __MODULO_H__
#include <sys/time.h> // Para la función gettimeofday

// Declaración de los prototipos de las funciones que se implementan en modulo.c

void InicioMuestra();

void FinMuestra();

void iniMatriz(int n, double *m1, double *m2);

void imprMatrices(int n, double *matriz);

// Implementa extern para las estructuras de tiempo
extern struct timeval ini, fin;

#endif