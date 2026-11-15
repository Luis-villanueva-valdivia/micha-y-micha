/*
 * Archivo:     liquidaciones.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.4
 * Descripcion: Implementacion del registro de liquidaciones. Se parte de
 *              los pagos sugeridos por simplificarDeudas, asi el deudor y
 *              el acreedor siempre son validos y el monto nunca pasa de
 *              lo que se debe (RF-12, CU-06).
 */
#include <stdio.h>
#include "liquidaciones.h"
#include "saldos.h"
#include "utilidades.h"

/*
 * Funcion:     siguienteIdLiquidacion
 * Descripcion: Calcula el id para una liquidacion nueva: el mayor id
 *              actual mas 1.
 * Parametros:  liquidaciones    - arreglo de liquidaciones
 *              numLiquidaciones - cuantas hay
 * Retorno:     El id disponible (1 si no hay liquidaciones).
 */
static int siguienteIdLiquidacion(const Liquidacion liquidaciones[],
                                  int numLiquidaciones) {
    int i = 0;
    int mayor = 0;

    for (i = 0; i < numLiquidaciones; i++) {
        if (liquidaciones[i].id > mayor) {
            mayor = liquidaciones[i].id;
        }
    }
    return mayor + 1;
}

/*
 * Funcion:     nombreUsuarioLiq
 * Descripcion: Busca el nombre de un usuario por su id.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay
 *              idUsuario   - id a buscar
 * Retorno:     Apuntador al nombre, o "(desconocido)" si no existe.
 */
static const char *nombreUsuarioLiq(const Usuario usuarios[], int numUsuarios,
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
 * Funcion:     registrarLiquidacion
 * Descripcion: Muestra los pagos sugeridos para quedar a mano y pide
 *              elegir el que se hizo. Pide el monto pagado (puede ser un
 *              pago parcial, pero no mayor a lo sugerido) y la fecha,
 *              muestra un resumen y, si se confirma, agrega la
 *              liquidacion. Avisa si ya hay MAX_LIQUIDACIONES.
 * Parametros:  liquidaciones    - arreglo de liquidaciones
 *              numLiquidaciones - apuntador al contador de liquidaciones
 *              idGrupo          - id del grupo activo
 *              usuarios, numUsuarios     - usuarios (para los nombres)
 *              miembros, numMiembros     - membresias
 *              gastos, numGastos         - gastos del sistema
 *              divisiones, numDivisiones - divisiones de los gastos
 * Retorno:     1 si se registro, 0 si no.
 */
int registrarLiquidacion(Liquidacion liquidaciones[], int *numLiquidaciones,
                         int idGrupo,
                         const Usuario usuarios[], int numUsuarios,
                         const MiembroGrupo miembros[], int numMiembros,
                         const Gasto gastos[], int numGastos,
                         const DivisionGasto divisiones[], int numDivisiones) {
    PagoSugerido pagos[MAX_MIEMBROS];
    Liquidacion nueva;
    int numPagos = 0;
    int opcion = 0;
    int i = 0;

    if (*numLiquidaciones >= MAX_LIQUIDACIONES) {
        printf("Error: Ya se alcanzo el maximo de %d liquidaciones.\n",
               MAX_LIQUIDACIONES);
        return 0;
    }

    numPagos = simplificarDeudas(idGrupo, miembros, numMiembros, gastos,
                                 numGastos, divisiones, numDivisiones,
                                 liquidaciones, *numLiquidaciones, pagos);
    if (numPagos == 0) {
        printf("No hay deudas pendientes.\n");
        return 0;
    }

    printf("\n--- Registrar liquidacion ---\n");
    for (i = 0; i < numPagos; i++) {
        printf("%d. %s le paga ", i + 1,
               nombreUsuarioLiq(usuarios, numUsuarios, pagos[i].idDeudor));
        mostrarMonto(pagos[i].montoCentavos);
        printf(" a %s\n",
               nombreUsuarioLiq(usuarios, numUsuarios, pagos[i].idAcreedor));
    }
    printf("0. Cancelar\n");
    printf("Elige el pago que se hizo: ");
    opcion = leerEntero(0, numPagos);
    if (opcion == 0) {
        return 0;
    }

    nueva.idGrupo = idGrupo;
    nueva.idDeudor = pagos[opcion - 1].idDeudor;
    nueva.idAcreedor = pagos[opcion - 1].idAcreedor;

    printf("Monto pagado (maximo ");
    mostrarMonto(pagos[opcion - 1].montoCentavos);
    printf("): ");
    nueva.montoCentavos = leerMonto();
    while (nueva.montoCentavos > pagos[opcion - 1].montoCentavos) {
        printf("Error: El monto no puede ser mayor a lo que se debe: ");
        nueva.montoCentavos = leerMonto();
    }
    printf("Fecha del pago (dd/mm/aaaa): ");
    nueva.fecha = leerFecha();

    printf("\n%s le paga ",
           nombreUsuarioLiq(usuarios, numUsuarios, nueva.idDeudor));
    mostrarMonto(nueva.montoCentavos);
    printf(" a %s el %02d/%02d/%04d\n",
           nombreUsuarioLiq(usuarios, numUsuarios, nueva.idAcreedor),
           nueva.fecha % 100, (nueva.fecha / 100) % 100, nueva.fecha / 10000);
    printf("Registrar el pago (1 = si, 0 = cancelar): ");
    if (leerEntero(0, 1) == 0) {
        printf("No se registro el pago.\n");
        return 0;
    }

    nueva.id = siguienteIdLiquidacion(liquidaciones, *numLiquidaciones);
    liquidaciones[*numLiquidaciones] = nueva;
    (*numLiquidaciones)++;

    printf("Pago registrado.\n");
    return 1;
}
