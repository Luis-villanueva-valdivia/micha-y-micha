/*
 * Archivo:     utilidades.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       29/10/2026
 * Version:     0.1
 * Descripcion: Funciones reutilizables para leer datos del teclado con
 *              validacion (enteros en rango, textos, montos y fechas) y
 *              para mostrar montos en pesos (RNF-02, RNF-03).
 */
#ifndef MICHAYMICHA_UTILIDADES_H
#define MICHAYMICHA_UTILIDADES_H

/* Descarta lo que quede en stdin hasta el fin de linea */
void limpiarBuffer(void);

/* Pide un entero hasta que este en [minimo, maximo] y lo devuelve */
int leerEntero(int minimo, int maximo);

/* Lee un texto no vacio de hasta capacidad - 1 caracteres en destino */
void leerTexto(char *destino, int capacidad);

/* Lee un monto como 840.50 y lo devuelve en centavos (84050) */
long leerMonto(void);

/* Lee una fecha dd/mm/aaaa valida y la devuelve como AAAAMMDD */
int leerFecha(void);

/* Imprime un monto en centavos como $840.50 */
void mostrarMonto(long montoCentavos);

#endif /* MICHAYMICHA_UTILIDADES_H */