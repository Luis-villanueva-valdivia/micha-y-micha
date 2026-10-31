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
#include <ctype.h>
#include "usuarios.h"
#include "utilidades.h"
#define MAX_INTENTOS_PIN 3 /* Intentos de PIN antes de regresar a la lista (E2) */

/*
 * Funcion:     esPinValido
 * Descripcion: Revisa que el texto tenga exactamente LONG_PIN caracteres
 *              y que todos sean digitos del 0 al 9.
 * Parametros:  pin - texto a revisar
 * Retorno:     1 si es valido, 0 si no.
 */
static int esPinValido(const char *pin) {
    int i = 0;

    if (strlen(pin) != LONG_PIN) {
        return 0;
    }
    for (i = 0; i < LONG_PIN; i++) {
        if (!isdigit(pin[i])) {
            return 0;
        }
    }
    return 1;
}

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
        printf("%d. %s", i + 1, usuarios[i].nombre);
        if (usuarios[i].esAdministrador) {
            printf(" (Administrador)");
        }
        printf("\n");
    }
}

/*
 * Funcion:     registrarUsuario
 * Descripcion: Pide el nombre y el PIN de un usuario nuevo y lo agrega al
 *              arreglo. No permite nombres repetidos. Si es el primer
 *              usuario del sistema, queda como Administrador (E3).
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - apuntador al contador de usuarios; aumenta en
 *                            1 si se agrega
 * Retorno:     1 si se registro, 0 si no (lleno o nombre repetido).
 */
int registrarUsuario(Usuario usuarios[], int *numUsuarios) {
    Usuario nuevo;
    char pinLeido[LONG_PIN + 2]; /* Un lugar extra para detectar PIN largos */
    int i = 0;

    if (*numUsuarios >= MAX_USUARIOS) {
        printf("Error: Ya no caben mas usuarios.\n");
        return 0;
    }

    printf("Nombre: ");
    leerTexto(nuevo.nombre, LONG_NOMBRE + 1);

    for (i = 0; i < *numUsuarios; i++) {
        if (strcmp(usuarios[i].nombre, nuevo.nombre) == 0) {
            printf("Error: Ya existe un usuario con ese nombre.\n");
            return 0;
        }
    }

    do {
        printf("PIN de %d digitos: ", LONG_PIN);
        leerTexto(pinLeido, LONG_PIN + 2); /* +1 para '\0', +1 para detectar PIN largos */
        if (!esPinValido(pinLeido)) {
            printf("Error: El PIN debe tener exactamente %d digitos.\n", LONG_PIN);
        }
    } while (!esPinValido(pinLeido));

    strcpy(nuevo.pin, pinLeido);
    nuevo.id=(*numUsuarios + 1); /* id unico, empieza en 1 */
    nuevo.esAdministrador = (*numUsuarios == 0) ? 1 : 0; /* Primer usuario es admin */

    usuarios[*numUsuarios] = nuevo;
    (*numUsuarios)++;

    printf("Usuario registrado.\n");
    return 1;
}

/*
 * Funcion:     iniciarSesion
 * Descripcion: Muestra la lista de usuarios para elegir uno y pide su PIN.
 *              Tras MAX_INTENTOS_PIN intentos fallidos regresa a la lista
 *              (E2). La opcion 0 regresa sin iniciar sesion.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay en el arreglo
 * Retorno:     La posicion del usuario en el arreglo, o -1 si no entro.
 */
int iniciarSesion(const Usuario usuarios[], int numUsuarios) {
    char pinLeido[LONG_PIN + 2];
    int opcion = 0;
    int posicion = 0;
    int intentos = 0;

    if (numUsuarios == 0) {
        printf("No hay usuarios registrados.\n");
        return -1;
    }

    do {
        printf("\n--- Iniciar sesion ---\n");
        listarUsuarios(usuarios, numUsuarios);
        printf("0. Regresar\n");
        printf("Elige tu usuario: ");
        opcion = leerEntero(0, numUsuarios);

        if (opcion == 0) {
            return -1;
        }
        posicion = opcion - 1; /* Convertir a indice de arreglo */

        for (intentos = 1; intentos <= MAX_INTENTOS_PIN; intentos++) {
            printf("PIN: ");
            leerTexto(pinLeido, LONG_PIN + 2);
            if (strcmp(pinLeido, usuarios[posicion].pin) == 0) {
                printf("Bienvenido, %s.\n", usuarios[posicion].nombre);
                return posicion;
            }
            printf("PIN incorrecto. Te quedan %d intentos.\n", MAX_INTENTOS_PIN - intentos);
        }
        printf("Demasiados intentos. Regresando a la lista.\n");
    } while (1);
}