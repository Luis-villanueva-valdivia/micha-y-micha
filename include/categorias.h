/*
 * Archivo:     categorias.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.2
 * Descripcion: Gestion de las categorias de gastos: listar, agregar,
 *              renombrar y eliminar (RF-05, CU-11).
 */
#ifndef MICHAYMICHA_CATEGORIAS_H
#define MICHAYMICHA_CATEGORIAS_H

#include "estructuras.h"

/* Muestra el numero y nombre de cada categoria para elegirla */
void listarCategorias(const Categoria categorias[], int numCategorias);

/* Devuelve la posicion de la categoria con ese id, o -1 si no existe */
int buscarCategoriaPorId(const Categoria categorias[], int numCategorias,
                         int idCategoria);

/* Pide el nombre de una categoria nueva y la agrega. Devuelve 1 si la
   agrego, 0 si no (llena o repetida). */
int agregarCategoria(Categoria categorias[], int *numCategorias);

/* Pide elegir una categoria y su nombre nuevo. Devuelve 1 si la
   renombro, 0 si no. */
int renombrarCategoria(Categoria categorias[], int numCategorias);

/* Pide elegir una categoria y la elimina si ningun gasto la usa.
   Devuelve 1 si la elimino, 0 si no. */
int eliminarCategoria(Categoria categorias[], int *numCategorias,
                      const Gasto gastos[], int numGastos);

#endif /* MICHAYMICHA_CATEGORIAS_H */
