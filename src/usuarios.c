/*
 * Archivo:     usuarios.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.1
 * Descripcion: Implementacion del alta de usuarios, el listado sin PIN y
 *              el inicio de sesion (RF-01, RF-02, RNF-08).
 */
#include <stdio.h>
#include <string.h>
#include "usuarios.h"
#include "utilidades.h"

/*
 * Funcion:     listarUsuarios
 * Descripcion: Muestra cada usuario con un numero para elegirlo (1, 2,
 *              3...) y su nombre. Marca al Administrador. Nunca muestra
 *              el PIN.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay en el arreglo
 * Retorno:     Ninguno.
 */
void listarUsuarios(const Usuario usuarios[], int numUsuarios) {
    int i = 0;

    for (i = 0; i < numUsuarios; i++) {
        printf("%d. %s", i+1, usuarios[i].nombre);
        if (usuarios[i].esAdministrador) {
            printf(" (Administrador)");
        }
        printf("\n");
    }
}