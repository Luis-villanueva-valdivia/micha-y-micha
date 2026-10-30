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
#define ARCHIVO_USUARIOS      "datos/usuarios.txt"
#define ARCHIVO_GRUPOS        "datos/grupos.txt"
#define ARCHIVO_MIEMBROS      "datos/miembros.txt"
#define ARCHIVO_CATEGORIAS    "datos/categorias.txt"
#define ARCHIVO_GASTOS        "datos/gastos.txt"
#define ARCHIVO_DIVISIONES    "datos/divisiones.txt"
#define ARCHIVO_LIQUIDACIONES "datos/liquidaciones.txt"

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

/* Guarda las categorias en ARCHIVO_CATEGORIAS. Devuelve 1 si pudo, 0 si
   no. */
int guardarCategorias(const Categoria categorias[], int numCategorias);

/* Carga las categorias de ARCHIVO_CATEGORIAS y deja en *numCategorias
   cuantas leyo. Devuelve 1 si pudo, 0 si no. */
int cargarCategorias(Categoria categorias[], int *numCategorias);

/* Guarda los gastos en ARCHIVO_GASTOS. Devuelve 1 si pudo, 0 si no. */
int guardarGastos(const Gasto gastos[], int numGastos);

/* Carga los gastos de ARCHIVO_GASTOS y deja en *numGastos cuantos leyo.
   Devuelve 1 si pudo, 0 si no. */
int cargarGastos(Gasto gastos[], int *numGastos);

/* Guarda las divisiones en ARCHIVO_DIVISIONES. Devuelve 1 si pudo, 0 si
   no. */
int guardarDivisiones(const DivisionGasto divisiones[], int numDivisiones);

/* Carga las divisiones de ARCHIVO_DIVISIONES y deja en *numDivisiones
   cuantas leyo. Devuelve 1 si pudo, 0 si no. */
int cargarDivisiones(DivisionGasto divisiones[], int *numDivisiones);

/* Guarda las liquidaciones en ARCHIVO_LIQUIDACIONES. Devuelve 1 si pudo,
   0 si no. */
int guardarLiquidaciones(const Liquidacion liquidaciones[],
                         int numLiquidaciones);

/* Carga las liquidaciones de ARCHIVO_LIQUIDACIONES y deja en
   *numLiquidaciones cuantas leyo. Devuelve 1 si pudo, 0 si no. */
int cargarLiquidaciones(Liquidacion liquidaciones[], int *numLiquidaciones);

#endif /* MICHAYMICHA_ARCHIVOS_H */
