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
#define ARCHIVO_GRUPOS     "datos/grupos.txt"
#define ARCHIVO_MIEMBROS   "datos/miembros.txt"

/* Guarda los usuarios en ARCHIVO_USUARIOS. Devuelve 1 si pudo, 0 si no. */
int guardarUsuarios(const Usuario usuarios[], int numUsuarios);

/* Carga los usuarios de ARCHIVO_USUARIOS en el arreglo y deja en
    *numUsuarios cuantos leyo. Devuelve 1 si pudo, 0 si no. */
int cargarUsuarios(Usuario usuarios[], int *numUsuarios);

/* Guarda los grupos en ARCHIVO_GRUPOS. Devuelve 1 si pudo, 0 si no. */
int guardarGrupos(const Grupo grupos[], int numGrupos);

/* Carga los grupos de ARCHIVO_GRUPOS y deja en *numGrupos cuantos leyo.
   Devuelve 1 si pudo, 0 si no. */
int cargarGrupos(Grupo grupos[], int *numGrupos);

/* Guarda las membresias en ARCHIVO_MIEMBROS. Devuelve 1 si pudo, 0 si no. */
int guardarMiembros(const MiembroGrupo miembros[], int numMiembros);

/* Carga las membresias de ARCHIVO_MIEMBROS y deja en *numMiembros cuantas
   leyo. Devuelve 1 si pudo, 0 si no. */
int cargarMiembros(MiembroGrupo miembros[], int *numMiembros);

#endif /* MICHAYMICHA_ARCHIVOS_H */
