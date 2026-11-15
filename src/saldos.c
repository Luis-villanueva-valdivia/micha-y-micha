/*
 * Archivo:     saldos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.4
 * Descripcion: Implementacion del calculo de saldos. Los montos se
 *              manejan en centavos (long) para que la suma de los saldos
 *              de un grupo sea exactamente cero (RF-10, RNF-04, CU-04).
 */
#include <stdio.h>
#include "saldos.h"
#include "utilidades.h"

/*
 * Funcion:     grupoDelGasto
 * Descripcion: Busca a que grupo pertenece un gasto.
 * Parametros:  gastos    - arreglo de gastos
 *              numGastos - cuantos gastos hay
 *              idGasto   - id del gasto
 * Retorno:     El id del grupo, o 0 si el gasto no existe.
 */
static int grupoDelGasto(const Gasto gastos[], int numGastos, int idGasto) {
    int i = 0;

    for (i = 0; i < numGastos; i++) {
        if (gastos[i].id == idGasto) {
            return gastos[i].idGrupo;
        }
    }
    return 0;
}

/*
 * Funcion:     saldoUsuario
 * Descripcion: Calcula el saldo de un usuario dentro de un grupo:
 *              + lo que pago en gastos del grupo
 *              - lo que le toca en las divisiones de esos gastos
 *              + lo que ha pagado en liquidaciones (como deudor)
 *              - lo que ha recibido en liquidaciones (como acreedor)
 * Parametros:  idGrupo   - id del grupo
 *              idUsuario - id del usuario
 *              gastos, numGastos               - gastos del sistema
 *              divisiones, numDivisiones       - divisiones de los gastos
 *              liquidaciones, numLiquidaciones - pagos entre miembros
 * Retorno:     El saldo en centavos (positivo = le deben, negativo = debe).
 */
long saldoUsuario(int idGrupo, int idUsuario,
                  const Gasto gastos[], int numGastos,
                  const DivisionGasto divisiones[], int numDivisiones,
                  const Liquidacion liquidaciones[], int numLiquidaciones) {
    long saldo = 0;
    int i = 0;

    for (i = 0; i < numGastos; i++) {
        if (gastos[i].idGrupo == idGrupo && gastos[i].idPagador == idUsuario) {
            saldo += gastos[i].montoCentavos;
        }
    }
    for (i = 0; i < numDivisiones; i++) {
        if (divisiones[i].idUsuario == idUsuario &&
            grupoDelGasto(gastos, numGastos, divisiones[i].idGasto) == idGrupo) {
            saldo -= divisiones[i].montoCentavos;
        }
    }
    for (i = 0; i < numLiquidaciones; i++) {
        if (liquidaciones[i].idGrupo == idGrupo) {
            if (liquidaciones[i].idDeudor == idUsuario) {
                saldo += liquidaciones[i].montoCentavos;
            }
            if (liquidaciones[i].idAcreedor == idUsuario) {
                saldo -= liquidaciones[i].montoCentavos;
            }
        }
    }
    return saldo;
}

/*
 * Funcion:     usuariosConSaldo
 * Descripcion: Revisa a cada miembro del grupo y copia en idsUsuarios a
 *              los que tienen saldo distinto de cero.
 * Parametros:  idGrupo                         - id del grupo
 *              miembros, numMiembros           - membresias
 *              gastos, numGastos               - gastos del sistema
 *              divisiones, numDivisiones       - divisiones de los gastos
 *              liquidaciones, numLiquidaciones - pagos entre miembros
 *              idsUsuarios - arreglo de salida (MAX_MIEMBROS lugares)
 * Retorno:     Cuantos miembros tienen saldo distinto de cero.
 */
int usuariosConSaldo(int idGrupo,
                     const MiembroGrupo miembros[], int numMiembros,
                     const Gasto gastos[], int numGastos,
                     const DivisionGasto divisiones[], int numDivisiones,
                     const Liquidacion liquidaciones[], int numLiquidaciones,
                     int idsUsuarios[]) {
    int i = 0;
    int cuantos = 0;

    for (i = 0; i < numMiembros && cuantos < MAX_MIEMBROS; i++) {
        if (miembros[i].idGrupo == idGrupo &&
            saldoUsuario(idGrupo, miembros[i].idUsuario, gastos, numGastos,
                         divisiones, numDivisiones, liquidaciones,
                         numLiquidaciones) != 0) {
            idsUsuarios[cuantos] = miembros[i].idUsuario;
            cuantos++;
        }
    }
    return cuantos;
}

/*
 * Funcion:     mostrarSaldos
 * Descripcion: Muestra el saldo de cada miembro del grupo con su
 *              significado (le deben / debe / al corriente) y, al final,
 *              la suma de todos los saldos, que siempre debe ser $0.00.
 * Parametros:  idGrupo                         - id del grupo
 *              usuarios, numUsuarios           - usuarios (para nombres)
 *              miembros, numMiembros           - membresias
 *              gastos, numGastos               - gastos del sistema
 *              divisiones, numDivisiones       - divisiones de los gastos
 *              liquidaciones, numLiquidaciones - pagos entre miembros
 * Retorno:     Ninguno.
 */
void mostrarSaldos(int idGrupo,
                   const Usuario usuarios[], int numUsuarios,
                   const MiembroGrupo miembros[], int numMiembros,
                   const Gasto gastos[], int numGastos,
                   const DivisionGasto divisiones[], int numDivisiones,
                   const Liquidacion liquidaciones[], int numLiquidaciones) {
    long saldo = 0;
    long suma = 0;
    int i = 0;
    int j = 0;

    printf("\n--- Saldos del grupo ---\n");
    for (i = 0; i < numMiembros; i++) {
        if (miembros[i].idGrupo != idGrupo) {
            continue;
        }
        saldo = saldoUsuario(idGrupo, miembros[i].idUsuario, gastos,
                             numGastos, divisiones, numDivisiones,
                             liquidaciones, numLiquidaciones);
        suma += saldo;

        for (j = 0; j < numUsuarios &&
                    usuarios[j].id != miembros[i].idUsuario; j++) {
            /* Solo avanza hasta encontrar al usuario */
        }
        printf("  %-20s ", (j < numUsuarios) ? usuarios[j].nombre
                                              : "(desconocido)");
        mostrarMonto(saldo);
        if (saldo > 0) {
            printf("   le deben\n");
        } else if (saldo < 0) {
            printf("   debe\n");
        } else {
            printf("   al corriente\n");
        }
    }
    printf("  Suma de saldos:      ");
    mostrarMonto(suma);
    printf("\n");
}
