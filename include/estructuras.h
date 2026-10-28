/*
 * Archivo:     estructuras.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       28/10/2026
 * Version:     0.1
 * Descripcion: Modelo de datos del sistema: los typedef struct de
 *              Usuario, Grupo, MiembroGrupo, Categoria, Gasto,
 *              DivisionGasto y Liquidacion, y las macros de capacidad
 *              que usan todos los modulos.
 */
#ifndef MICHAYMICHA_ESTRUCTURAS_H
#define MICHAYMICHA_ESTRUCTURAS_H

/* Capacidades del sistema (RNF-06). Se ajustan cambiando solo aqui. */
#define MAX_MIEMBROS    10  /* Miembros por grupo */
#define MAX_GRUPOS      5   /* Grupos en el sistema */
#define MAX_CATEGORIAS  20  /* Categorias en el sistema */
#define MAX_GASTOS      500 /* Gastos en total */

#endif /* MICHAYMICHA_ESTRUCTURAS_H */

