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
#include <string.h>
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
    int valido = 0;

    do {
        leidos = scanf("%d", &numero);
        limpiarBuffer();
        valido = (leidos == 1) && (numero >= minimo && numero <= maximo);
        if (!valido) {
            printf("Error: Ingrese un numero entre %d y %d: ", minimo, maximo);
        }
    } while (!valido);

    return numero;
}

/*
 * Funcion:     mostrarMonto
 * Descripcion: Imprime un monto en centavos con formato de pesos y dos
 *              decimales, por ejemplo 84050 como $840.50. Los negativos
 *              se muestran como -$1.50. No imprime salto de linea.
 * Parametros:  montoCentavos - monto a mostrar, en centavos
 * Retorno:     Ninguno.
 */
void mostrarMonto(long montoCentavos) {
    if (montoCentavos < 0) {
        printf("-");
        montoCentavos = -montoCentavos;
    }
    printf("$%ld.%02ld", montoCentavos / 100, montoCentavos % 100);
}

/*
 * Funcion:     leerTexto
 * Descripcion: Lee una linea de texto no vacia con fgets, sin desbordar
 *              el arreglo, y le quita el salto de linea final. Si el
 *              texto excede la capacidad, se trunca y se descarta el
 *              resto de la linea.
 * Parametros:  destino   - arreglo donde se guarda el texto
 *              capacidad - tamano del arreglo destino (incluye el '\0')
 * Retorno:     Ninguno.
 * Precondic.:  capacidad >= 2.
 */
void leerTexto(char *destino, int capacidad) {
    int longitud = 0;

    do {
        fgets(destino, capacidad, stdin);
        longitud = strlen(destino);
        if (longitud > 0 && destino[longitud - 1] == '\n') {
            destino[longitud - 1] = '\0';
            longitud--;
        } else {
            limpiarBuffer();
        }
        if (longitud == 0) {
            printf("Error: El texto no puede estar vacio: ");
        }
    } while (longitud == 0);
}
