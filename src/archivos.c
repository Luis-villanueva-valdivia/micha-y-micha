/*
 * Archivo:     archivos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.1
 * Descripcion: Implementacion del guardado y la carga de datos en archivos
 *              de texto con campos separados por '|' (RF-16, RF-17).
 */
#include <stdio.h>
#include "archivos.h"

/*
 * Funcion:     guardarUsuarios
 * Descripcion: Escribe todos los usuarios en ARCHIVO_USUARIOS, uno por
 *              linea con el formato id|nombre|pin|esAdministrador. Si el
 *              archivo ya existia, se reemplaza.
 * Parametros:  usuarios    - arreglo de usuarios a guardar (entrada)
 *              numUsuarios - cuantos usuarios hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarUsuarios(const Usuario usuarios[], int numUsuarios) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numUsuarios; i++) {
        fprintf(archivo, "%d|%s|%s|%d\n", usuarios[i].id, usuarios[i].nombre,
                usuarios[i].pin, usuarios[i].esAdministrador);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarUsuarios
 * Descripcion: Lee los usuarios de ARCHIVO_USUARIOS (una linea por
 *              usuario, campos separados por '|') y los guarda en el
 *              arreglo. Las lineas danadas se ignoran. Lee como maximo
 *              MAX_USUARIOS.
 * Parametros:  usuarios    - arreglo donde se guardan (salida)
 *              numUsuarios - cuantos usuarios se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no existe o no se
 *              pudo abrir (en ese caso *numUsuarios queda en 0).
 */
int cargarUsuarios(Usuario usuarios[], int *numUsuarios) {
    FILE *archivo = NULL;
    char linea[100];
    Usuario leido;
    int campos = 0;

    *numUsuarios = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numUsuarios < MAX_USUARIOS) {
         /* Los anchos 30 y 4 deben coincidir con LONG_NOMBRE y LONG_PIN */
        campos = sscanf(linea, "%d|%30[^|]|%4[^|]|%d", &leido.id, leido.nombre,
                        leido.pin, &leido.esAdministrador);
        if (campos == 4) {
            usuarios[*numUsuarios] = leido;
            (*numUsuarios)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarGrupos
 * Descripcion: Escribe todos los grupos en ARCHIVO_GRUPOS, uno por linea
 *              con el formato id|nombre|idAdministrador.
 * Parametros:  grupos    - arreglo de grupos a guardar (entrada)
 *              numGrupos - cuantos grupos hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarGrupos(const Grupo grupos[], int numGrupos) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_GRUPOS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numGrupos; i++) {
        fprintf(archivo, "%d|%s|%d\n", grupos[i].id, grupos[i].nombre,
                grupos[i].idAdministrador);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarGrupos
 * Descripcion: Lee los grupos de ARCHIVO_GRUPOS. Las lineas danadas se
 *              ignoran. Lee como maximo MAX_GRUPOS.
 * Parametros:  grupos    - arreglo donde se guardan (salida)
 *              numGrupos - cuantos grupos se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numGrupos en 0).
 */
int cargarGrupos(Grupo grupos[], int *numGrupos) {
    FILE *archivo = NULL;
    char linea[100];
    Grupo leido;
    int campos = 0;

    *numGrupos = 0;

    archivo = fopen(ARCHIVO_GRUPOS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numGrupos < MAX_GRUPOS) {
        /* El ancho 30 debe coincidir con LONG_NOMBRE */
        campos = sscanf(linea, "%d|%30[^|]|%d", &leido.id, leido.nombre,
                        &leido.idAdministrador);
        if (campos == 3) {
            grupos[*numGrupos] = leido;
            (*numGrupos)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarMiembros
 * Descripcion: Escribe todas las membresias en ARCHIVO_MIEMBROS, una por
 *              linea con el formato idGrupo|idUsuario.
 * Parametros:  miembros    - arreglo de membresias a guardar (entrada)
 *              numMiembros - cuantas membresias hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarMiembros(const MiembroGrupo miembros[], int numMiembros) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_MIEMBROS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numMiembros; i++) {
        fprintf(archivo, "%d|%d\n", miembros[i].idGrupo, miembros[i].idUsuario);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarMiembros
 * Descripcion: Lee las membresias de ARCHIVO_MIEMBROS. Las lineas danadas
 *              se ignoran. Lee como maximo MAX_MEMBRESIAS.
 * Parametros:  miembros    - arreglo donde se guardan (salida)
 *              numMiembros - cuantas membresias se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numMiembros en 0).
 */
int cargarMiembros(MiembroGrupo miembros[], int *numMiembros) {
    FILE *archivo = NULL;
    char linea[100];
    MiembroGrupo leido;
    int campos = 0;

    *numMiembros = 0;

    archivo = fopen(ARCHIVO_MIEMBROS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numMiembros < MAX_MEMBRESIAS) {
        campos = sscanf(linea, "%d|%d", &leido.idGrupo, &leido.idUsuario);
        if (campos == 2) {
            miembros[*numMiembros] = leido;
            (*numMiembros)++;
        }
    }

    fclose(archivo);
    return 1;
}
