/*
 * Archivo:     reportes.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     1.0
 * Descripcion: Reportes del grupo activo: historial de gastos ordenado
 *              por fecha (RF-13, CU-07) y gastos por categoria (RF-14,
 *              CU-08).
 */
#ifndef MICHAYMICHA_REPORTES_H
#define MICHAYMICHA_REPORTES_H

#include "estructuras.h"

/* Pide ver todo o un mes y muestra los gastos del grupo del mas reciente
   al mas antiguo, con su total */
void mostrarHistorial(int idGrupo,
                      const Gasto gastos[], int numGastos,
                      const Usuario usuarios[], int numUsuarios,
                      const Categoria categorias[], int numCategorias);

/* Pide ver todo o un mes y muestra cuanto se gasto en cada categoria,
   con su porcentaje del total, de la mayor a la menor */
void reportePorCategoria(int idGrupo,
                         const Gasto gastos[], int numGastos,
                         const Categoria categorias[], int numCategorias);

#endif /* MICHAYMICHA_REPORTES_H */
