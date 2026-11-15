/*
 * Archivo:     grupos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.2
 * Descripcion: Implementacion de la gestion de grupos: listar, crear,
 *              renombrar y eliminar (RF-03, CU-09).
 */
#include <stdio.h>
#include <string.h>
#include "grupos.h"
#include "utilidades.h"

/*
 * Funcion:     existeNombreGrupo
 * Descripcion: Revisa si ya hay un grupo con ese nombre, sin contar el
 *              grupo en la posicion ignorar (sirve al renombrar).
 * Parametros:  grupos    - arreglo de grupos
 *              numGrupos - cuantos grupos hay en el arreglo
 *              nombre    - nombre a buscar
 *              ignorar   - posicion que no se compara, o -1 para ninguna
 * Retorno:     1 si el nombre ya existe, 0 si no.
 */
static int existeNombreGrupo(const Grupo grupos[], int numGrupos,
                             const char *nombre, int ignorar) {
    int i = 0;

    for (i = 0; i < numGrupos; i++) {
        if (i != ignorar && strcmp(grupos[i].nombre, nombre) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * Funcion:     siguienteIdGrupo
 * Descripcion: Calcula el id para un grupo nuevo: el mayor id actual mas
 *              1. Asi no se repiten ids aunque se eliminen grupos.
 * Parametros:  grupos    - arreglo de grupos
 *              numGrupos - cuantos grupos hay en el arreglo
 * Retorno:     El id disponible (1 si no hay grupos).
 */
static int siguienteIdGrupo(const Grupo grupos[], int numGrupos) {
    int i = 0;
    int mayor = 0;

    for (i = 0; i < numGrupos; i++) {
        if (grupos[i].id > mayor) {
            mayor = grupos[i].id;
        }
    }
    return mayor + 1;
}

/*
 * Funcion:     listarGrupos
 * Descripcion: Muestra cada grupo con un numero para elegirlo (1, 2,
 *              3...) y su nombre.
 * Parametros:  grupos    - arreglo de grupos
 *              numGrupos - cuantos grupos hay en el arreglo
 * Retorno:     Ninguno.
 */
void listarGrupos(const Grupo grupos[], int numGrupos) {
    int i = 0;

    for (i = 0; i < numGrupos; i++) {
        printf("%d. %s\n", i + 1, grupos[i].nombre);
    }
}

/*
 * Funcion:     buscarGrupoPorId
 * Descripcion: Busca un grupo por su id.
 * Parametros:  grupos    - arreglo de grupos
 *              numGrupos - cuantos grupos hay en el arreglo
 *              idGrupo   - id a buscar
 * Retorno:     La posicion del grupo en el arreglo, o -1 si no existe.
 */
int buscarGrupoPorId(const Grupo grupos[], int numGrupos, int idGrupo) {
    int i = 0;

    for (i = 0; i < numGrupos; i++) {
        if (grupos[i].id == idGrupo) {
            return i;
        }
    }
    return -1;
}

/*
 * Funcion:     crearGrupo
 * Descripcion: Pide el nombre de un grupo nuevo y lo agrega al arreglo.
 *              Rechaza nombres repetidos (E1) y avisa si ya hay
 *              MAX_GRUPOS grupos (E3). El nombre vacio lo rechaza
 *              leerTexto.
 * Parametros:  grupos          - arreglo de grupos
 *              numGrupos       - apuntador al contador; aumenta en 1 si
 *                                se agrega
 *              idAdministrador - id del usuario que administra el grupo
 * Retorno:     1 si se creo, 0 si no.
 */
int crearGrupo(Grupo grupos[], int *numGrupos, int idAdministrador) {
    Grupo nuevo;

    if (*numGrupos >= MAX_GRUPOS) {
        printf("Error: Ya se alcanzo el maximo de %d grupos.\n", MAX_GRUPOS);
        return 0;
    }

    printf("Nombre del grupo: ");
    leerTexto(nuevo.nombre, LONG_NOMBRE + 1);

    if (existeNombreGrupo(grupos, *numGrupos, nuevo.nombre, -1)) {
        printf("Error: Ya existe un grupo con ese nombre.\n");
        return 0;
    }

    nuevo.id = siguienteIdGrupo(grupos, *numGrupos);
    nuevo.idAdministrador = idAdministrador;

    grupos[*numGrupos] = nuevo;
    (*numGrupos)++;

    printf("Grupo \"%s\" creado.\n", nuevo.nombre);
    return 1;
}
