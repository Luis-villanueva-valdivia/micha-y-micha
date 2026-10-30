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

/*
 * Funcion:     limpiarBuffer
 * Descripcion: Descarta los caracteres que quedan en stdin hasta el fin
 *              de linea, para que una entrada invalida no afecte la
 *              siguiente lectura.
 * Parametros:  Ninguno.
 * Retorno:     Ninguno.
 */
void limpiarBuffer(void) {
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Solo se descarta el caracter */
    }
}
/*
 * Funcion:     leerEntero
 * Descripcion: Lee un entero del teclado y lo vuelve a pedir mientras no
 *              sea un numero o este fuera del rango [minimo, maximo].
 * Parametros:  minimo - valor minimo aceptado
 *              maximo - valor maximo aceptado
 * Retorno:     El entero valido que escribio el usuario.
 * Precondic.:  minimo <= maximo.
 */
int leerEntero(int minimo, int maximo) {
    int numero = 0;
    int leidos = 0;
    int valido =0;

    do{
        leidos=scanf("%d", &numero);
        limpiarBuffer();
        valido =(leidos==1) && (numero>=minimo && numero<=maximo);
        if(!valido){
            printf("Error: Ingrese un numero entre %d y %d: ", minimo, maximo);
        }
    } while(!valido);

    return numero;
}
