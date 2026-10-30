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