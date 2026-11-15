/*
 * Archivo:     liquidaciones.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.4
 * Descripcion: Registro de liquidaciones: pagos reales entre miembros
 *              para saldar las deudas del grupo (RF-12, CU-06).
 */
#ifndef MICHAYMICHA_LIQUIDACIONES_H
#define MICHAYMICHA_LIQUIDACIONES_H

#include "estructuras.h"

/* Muestra los pagos sugeridos del grupo, pide elegir uno, el monto
   pagado (sin pasar de lo sugerido) y la fecha, y si se confirma agrega
   la liquidacion. Devuelve 1 si se registro, 0 si no. */
int registrarLiquidacion(Liquidacion liquidaciones[], int *numLiquidaciones,
                         int idGrupo,
                         const Usuario usuarios[], int numUsuarios,
                         const MiembroGrupo miembros[], int numMiembros,
                         const Gasto gastos[], int numGastos,
                         const DivisionGasto divisiones[], int numDivisiones);

#endif /* MICHAYMICHA_LIQUIDACIONES_H */
