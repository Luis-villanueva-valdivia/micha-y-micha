/*
 * Archivo:     saldos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.4
 * Descripcion: Implementacion del calculo de saldos y de la
 *              simplificacion de deudas. Los montos se manejan en
 *              centavos (long) para que la suma de los saldos de un grupo
 *              sea exactamente cero (RF-10, RF-11, RNF-04, CU-04, CU-05).
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

/*
 * Funcion:     nombreDe
 * Descripcion: Busca el nombre de un usuario por su id.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay
 *              idUsuario   - id a buscar
 * Retorno:     Apuntador al nombre, o "(desconocido)" si no existe.
 */
static const char *nombreDe(const Usuario usuarios[], int numUsuarios,
                            int idUsuario) {
    int i = 0;

    for (i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == idUsuario) {
            return usuarios[i].nombre;
        }
    }
    return "(desconocido)";
}

/*
 * Funcion:     simplificarDeudas
 * Descripcion: Calcula los saldos de los miembros del grupo y, mientras
 *              alguien deba, hace que el que mas debe le pague al que mas
 *              le deben la menor de las dos cantidades. Cada pago deja al
 *              menos a uno de los dos en cero, por lo que con n miembros
 *              hay como maximo n - 1 pagos (RF-11, CU-05).
 * Parametros:  idGrupo                         - id del grupo
 *              miembros, numMiembros           - membresias
 *              gastos, numGastos               - gastos del sistema
 *              divisiones, numDivisiones       - divisiones de los gastos
 *              liquidaciones, numLiquidaciones - pagos ya registrados
 *              pagos - arreglo de salida (MAX_MIEMBROS lugares)
 * Retorno:     Cuantos pagos se generaron.
 */
int simplificarDeudas(int idGrupo,
                      const MiembroGrupo miembros[], int numMiembros,
                      const Gasto gastos[], int numGastos,
                      const DivisionGasto divisiones[], int numDivisiones,
                      const Liquidacion liquidaciones[], int numLiquidaciones,
                      PagoSugerido pagos[]) {
    int ids[MAX_MIEMBROS];     /* id de cada miembro del grupo */
    long saldos[MAX_MIEMBROS]; /* saldo de cada miembro, mismo orden */
    int total = 0;
    int numPagos = 0;
    int deudor = 0;    /* posicion del que mas debe */
    int acreedor = 0;  /* posicion del que mas le deben */
    long monto = 0;
    int i = 0;

    for (i = 0; i < numMiembros && total < MAX_MIEMBROS; i++) {
        if (miembros[i].idGrupo == idGrupo) {
            ids[total] = miembros[i].idUsuario;
            saldos[total] = saldoUsuario(idGrupo, ids[total], gastos,
                                         numGastos, divisiones, numDivisiones,
                                         liquidaciones, numLiquidaciones);
            total++;
        }
    }

    while (numPagos < MAX_MIEMBROS) {
        deudor = 0;
        acreedor = 0;
        for (i = 1; i < total; i++) {
            if (saldos[i] < saldos[deudor]) {
                deudor = i;
            }
            if (saldos[i] > saldos[acreedor]) {
                acreedor = i;
            }
        }
        if (total == 0 || saldos[deudor] >= 0 || saldos[acreedor] <= 0) {
            break; /* Ya nadie debe */
        }

        /* Se paga lo menor entre lo que debe uno y lo que le deben al otro */
        monto = -saldos[deudor];
        if (saldos[acreedor] < monto) {
            monto = saldos[acreedor];
        }
        pagos[numPagos].idDeudor = ids[deudor];
        pagos[numPagos].idAcreedor = ids[acreedor];
        pagos[numPagos].montoCentavos = monto;
        numPagos++;

        saldos[deudor] += monto;
        saldos[acreedor] -= monto;
    }
    return numPagos;
}

/*
 * Funcion:     mostrarDeudasSimplificadas
 * Descripcion: Muestra la lista de pagos que deja al grupo al corriente,
 *              o avisa que no hay deudas pendientes.
 * Parametros:  idGrupo                         - id del grupo
 *              usuarios, numUsuarios           - usuarios (para nombres)
 *              miembros, numMiembros           - membresias
 *              gastos, numGastos               - gastos del sistema
 *              divisiones, numDivisiones       - divisiones de los gastos
 *              liquidaciones, numLiquidaciones - pagos ya registrados
 * Retorno:     Ninguno.
 */
void mostrarDeudasSimplificadas(int idGrupo,
                                const Usuario usuarios[], int numUsuarios,
                                const MiembroGrupo miembros[], int numMiembros,
                                const Gasto gastos[], int numGastos,
                                const DivisionGasto divisiones[],
                                int numDivisiones,
                                const Liquidacion liquidaciones[],
                                int numLiquidaciones) {
    PagoSugerido pagos[MAX_MIEMBROS];
    int numPagos = 0;
    int i = 0;

    numPagos = simplificarDeudas(idGrupo, miembros, numMiembros, gastos,
                                 numGastos, divisiones, numDivisiones,
                                 liquidaciones, numLiquidaciones, pagos);

    printf("\n--- Pagos para quedar a mano ---\n");
    if (numPagos == 0) {
        printf("No hay deudas pendientes.\n");
        return;
    }
    for (i = 0; i < numPagos; i++) {
        printf("%d. %s le paga ", i + 1,
               nombreDe(usuarios, numUsuarios, pagos[i].idDeudor));
        mostrarMonto(pagos[i].montoCentavos);
        printf(" a %s\n", nombreDe(usuarios, numUsuarios, pagos[i].idAcreedor));
    }
}
