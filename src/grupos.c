/*
 * Archivo:     grupos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.2
 * Descripcion: Implementacion de la gestion de grupos: listar, crear,
 *              renombrar y eliminar (RF-03, CU-09), y de sus miembros:
 *              agregar y quitar (RF-04, CU-10).
 */
#include <stdio.h>
#include <string.h>
#include "grupos.h"
#include "usuarios.h"
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

/*
 * Funcion:     elegirGrupo
 * Descripcion: Muestra la lista de grupos y pide elegir uno. La opcion 0
 *              cancela.
 * Parametros:  grupos    - arreglo de grupos
 *              numGrupos - cuantos grupos hay en el arreglo
 * Retorno:     La posicion del grupo elegido, o -1 si se cancelo o no
 *              hay grupos.
 */
static int elegirGrupo(const Grupo grupos[], int numGrupos) {
    int opcion = 0;

    if (numGrupos == 0) {
        printf("No hay grupos registrados.\n");
        return -1;
    }
    listarGrupos(grupos, numGrupos);
    printf("0. Cancelar\n");
    printf("Elige el grupo: ");
    opcion = leerEntero(0, numGrupos);
    return opcion - 1; /* 0 se convierte en -1 (cancelar) */
}

/*
 * Funcion:     renombrarGrupo
 * Descripcion: Pide elegir un grupo y le cambia el nombre. Rechaza
 *              nombres repetidos (E1).
 * Parametros:  grupos    - arreglo de grupos
 *              numGrupos - cuantos grupos hay en el arreglo
 * Retorno:     1 si se renombro, 0 si no.
 */
int renombrarGrupo(Grupo grupos[], int numGrupos) {
    char nombre[LONG_NOMBRE + 1];
    int posicion = 0;

    posicion = elegirGrupo(grupos, numGrupos);
    if (posicion == -1) {
        return 0;
    }

    printf("Nuevo nombre: ");
    leerTexto(nombre, LONG_NOMBRE + 1);

    if (existeNombreGrupo(grupos, numGrupos, nombre, posicion)) {
        printf("Error: Ya existe un grupo con ese nombre.\n");
        return 0;
    }

    strcpy(grupos[posicion].nombre, nombre);
    printf("Grupo renombrado.\n");
    return 1;
}

/*
 * Funcion:     eliminarGrupo
 * Descripcion: Pide elegir un grupo, confirma y lo elimina del arreglo
 *              junto con sus membresias. Los elementos siguientes se
 *              recorren una posicion para no dejar huecos.
 * Parametros:  grupos      - arreglo de grupos
 *              numGrupos   - apuntador al contador de grupos
 *              miembros    - arreglo de membresias
 *              numMiembros - apuntador al contador de membresias
 * Retorno:     El id del grupo eliminado, o 0 si no se elimino.
 */
int eliminarGrupo(Grupo grupos[], int *numGrupos,
                  MiembroGrupo miembros[], int *numMiembros) {
    int posicion = 0;
    int idGrupo = 0;
    int i = 0;
    int j = 0;

    posicion = elegirGrupo(grupos, *numGrupos);
    if (posicion == -1) {
        return 0;
    }

    printf("Se eliminara \"%s\". Confirmar (1 = si, 0 = no): ",
           grupos[posicion].nombre);
    if (leerEntero(0, 1) == 0) {
        printf("No se elimino el grupo.\n");
        return 0;
    }

    idGrupo = grupos[posicion].id;

    /* Recorre los grupos siguientes una posicion a la izquierda */
    for (i = posicion; i < *numGrupos - 1; i++) {
        grupos[i] = grupos[i + 1];
    }
    (*numGrupos)--;

    /* Quita las membresias del grupo, conservando las demas en orden */
    for (i = 0; i < *numMiembros; i++) {
        if (miembros[i].idGrupo != idGrupo) {
            miembros[j] = miembros[i];
            j++;
        }
    }
    *numMiembros = j;

    printf("Grupo eliminado.\n");
    return idGrupo;
}

/*
 * Funcion:     buscarUsuarioPorId
 * Descripcion: Busca un usuario por su id.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay en el arreglo
 *              idUsuario   - id a buscar
 * Retorno:     La posicion del usuario en el arreglo, o -1 si no existe.
 */
static int buscarUsuarioPorId(const Usuario usuarios[], int numUsuarios,
                              int idUsuario) {
    int i = 0;

    for (i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == idUsuario) {
            return i;
        }
    }
    return -1;
}

/*
 * Funcion:     esMiembro
 * Descripcion: Revisa si existe la membresia (idGrupo, idUsuario).
 * Parametros:  miembros    - arreglo de membresias
 *              numMiembros - cuantas membresias hay en el arreglo
 *              idGrupo     - id del grupo
 *              idUsuario   - id del usuario
 * Retorno:     1 si el usuario pertenece al grupo, 0 si no.
 */
int esMiembro(const MiembroGrupo miembros[], int numMiembros, int idGrupo,
              int idUsuario) {
    int i = 0;

    for (i = 0; i < numMiembros; i++) {
        if (miembros[i].idGrupo == idGrupo &&
            miembros[i].idUsuario == idUsuario) {
            return 1;
        }
    }
    return 0;
}

/*
 * Funcion:     contarMiembros
 * Descripcion: Cuenta las membresias que pertenecen a un grupo.
 * Parametros:  miembros    - arreglo de membresias
 *              numMiembros - cuantas membresias hay en el arreglo
 *              idGrupo     - id del grupo
 * Retorno:     El numero de miembros del grupo.
 */
int contarMiembros(const MiembroGrupo miembros[], int numMiembros,
                   int idGrupo) {
    int i = 0;
    int cuenta = 0;

    for (i = 0; i < numMiembros; i++) {
        if (miembros[i].idGrupo == idGrupo) {
            cuenta++;
        }
    }
    return cuenta;
}

/*
 * Funcion:     listarMiembros
 * Descripcion: Muestra con un numero (1, 2, 3...) el nombre de cada
 *              miembro del grupo. Si no tiene miembros, lo indica.
 * Parametros:  miembros    - arreglo de membresias
 *              numMiembros - cuantas membresias hay en el arreglo
 *              idGrupo     - id del grupo
 *              usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay en el arreglo
 * Retorno:     Ninguno.
 */
void listarMiembros(const MiembroGrupo miembros[], int numMiembros,
                    int idGrupo, const Usuario usuarios[], int numUsuarios) {
    int i = 0;
    int numero = 0;
    int posicion = 0;

    for (i = 0; i < numMiembros; i++) {
        if (miembros[i].idGrupo == idGrupo) {
            posicion = buscarUsuarioPorId(usuarios, numUsuarios,
                                          miembros[i].idUsuario);
            numero++;
            if (posicion != -1) {
                printf("%d. %s\n", numero, usuarios[posicion].nombre);
            } else {
                printf("%d. (usuario no encontrado)\n", numero);
            }
        }
    }
    if (numero == 0) {
        printf("El grupo no tiene miembros.\n");
    }
}
