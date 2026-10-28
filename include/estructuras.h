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

/* Capacidades derivadas de las anteriores */
#define MAX_USUARIOS    (MAX_GRUPOS * MAX_MIEMBROS)  /* Usuarios en el sistema */
#define MAX_MEMBRESIAS  (MAX_GRUPOS * MAX_MIEMBROS)  /* Pertenencias usuario-grupo en total */
#define MAX_DIVISIONES  (MAX_GASTOS * MAX_MIEMBROS)  /* Divisiones de gastos en total */
#define MAX_LIQUIDACIONES MAX_GASTOS                 /* Liquidaciones en total */

/* Longitudes de texto: maximo de caracteres que puede escribir el usuario.
   Los arreglos de char se declaran con + 1 para el '\0' final. */
#define LONG_NOMBRE      30 /* Nombre de usuario, grupo o categoria */
#define LONG_PIN         4 /* PIN de usuario */
#define LONG_DESCRIPCION 50 /* Descripcion de gasto */

#endif /* MICHAYMICHA_ESTRUCTURAS_H */


