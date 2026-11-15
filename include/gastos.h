/*
 * Archivo:     gastos.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.3
 * Descripcion: Registro de gastos compartidos del grupo activo y de sus
 *              participantes (RF-06, CU-02), y su division en partes
 *              iguales o personalizadas (RF-07, RF-08, CU-03).
 */
#ifndef MICHAYMICHA_GASTOS_H
#define MICHAYMICHA_GASTOS_H

#include "estructuras.h"

/* Reparte montoCentavos en partes iguales entre numParticipantes y deja
   cada parte en partes[]. El residuo se asigna al pagador si participa
   (si no, al primero), de modo que la suma es exactamente el total. */
void dividirIgual(long montoCentavos, const int idsParticipantes[],
                  int numParticipantes, int idPagador, long partes[]);

/* Pide la parte de cada participante (montos mayores que 0) hasta que la
   suma sea exactamente montoCentavos, y las deja en partes[]. */
void dividirPersonalizado(long montoCentavos, const int idsParticipantes[],
                          int numParticipantes, const Usuario usuarios[],
                          int numUsuarios, long partes[]);

/* Pide los datos de un gasto del grupo idGrupo (descripcion, monto,
   fecha, categoria, pagador y participantes), muestra un resumen y, si se
   confirma, lo agrega junto con una division por participante. Devuelve
   1 si se registro, 0 si se cancelo o no cabe. */
int registrarGasto(Gasto gastos[], int *numGastos,
                   DivisionGasto divisiones[], int *numDivisiones,
                   int idGrupo,
                   const Usuario usuarios[], int numUsuarios,
                   const MiembroGrupo miembros[], int numMiembros,
                   const Categoria categorias[], int numCategorias);

#endif /* MICHAYMICHA_GASTOS_H */
