/*
 * Archivo:     utilidades.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       29/10/2026
 * Version:     0.1
 * Descripcion: Implementacion de la lectura validada de entradas y del
 *              formato de montos en pesos (RNF-02, RNF-03).
 */
#include <stdio.h>
#include "utilidades.h"

void limpiarBuffer(void) {
    int c = 0; 
    while((c = getchar()) != '\n' && c != EOF){

    }
}