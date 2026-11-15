/*
 * Archivo:     saldos.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.4
 * Descripcion: Calculo y consulta de los saldos de los miembros de un
 *              grupo a partir de gastos, divisiones y liquidaciones
 *              (RF-10, CU-04).
 */
#ifndef MICHAYMICHA_SALDOS_H
#define MICHAYMICHA_SALDOS_H

#include "estructuras.h"

/* Saldo de un usuario en un grupo, en centavos: lo que pago menos lo que
   le toca, mas lo que ha liquidado menos lo que ha recibido. Positivo =
   le deben; negativo = debe. */
long saldoUsuario(int idGrupo, int idUsuario,
                  const Gasto gastos[], int numGastos,
                  const DivisionGasto divisiones[], int numDivisiones,
                  const Liquidacion liquidaciones[], int numLiquidaciones);

/* Copia en idsUsuarios los miembros del grupo con saldo distinto de cero
   y devuelve cuantos son. */
int usuariosConSaldo(int idGrupo,
                     const MiembroGrupo miembros[], int numMiembros,
                     const Gasto gastos[], int numGastos,
                     const DivisionGasto divisiones[], int numDivisiones,
                     const Liquidacion liquidaciones[], int numLiquidaciones,
                     int idsUsuarios[]);

/* Muestra la tabla de saldos de los miembros del grupo */
void mostrarSaldos(int idGrupo,
                   const Usuario usuarios[], int numUsuarios,
                   const MiembroGrupo miembros[], int numMiembros,
                   const Gasto gastos[], int numGastos,
                   const DivisionGasto divisiones[], int numDivisiones,
                   const Liquidacion liquidaciones[], int numLiquidaciones);

#endif /* MICHAYMICHA_SALDOS_H */
