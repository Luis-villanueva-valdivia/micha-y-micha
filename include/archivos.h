/*
 * Archivo:     archivos.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.1
 * Descripcion: Guardado y carga de los datos del sistema en archivos de
 *              texto dentro de datos/, uno por estructura (RF-16, RF-17,
 *              RNF-07).
 */
#ifndef MICHAYMICHA_ARCHIVOS_H
#define MICHAYMICHA_ARCHIVOS_H

#include "estructuras.h"

/* Rutas de los archivos de datos (un archivo por estructura) */
#define ARCHIVO_USUARIOS "datos/usuarios.txt"

/* Guarda los usuarios en ARCHIVO_USUARIOS. Devuelve 1 si pudo, 0 si no. */
int guardarUsuarios(const Usuario usuarios[], int numUsuarios);

/* Carga los usuarios de ARCHIVO_USUARIOS en el arreglo y deja en
    *numUsuarios cuantos leyo. Devuelve 1 si pudo, 0 si no. */
int cargarUsuarios(Usuario usuarios[], int *numUsuarios);

#endif /* MICHAYMICHA_ARCHIVOS_H */
