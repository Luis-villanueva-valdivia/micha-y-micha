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