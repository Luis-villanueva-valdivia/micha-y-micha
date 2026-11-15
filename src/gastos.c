/*
 * Archivo:     gastos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.3
 * Descripcion: Implementacion del registro de gastos: captura de datos,
 *              eleccion de pagador y participantes, division en partes
 *              iguales o personalizadas, resumen y confirmacion (RF-06,
 *              RF-07, RF-08, CU-02, CU-03), y eliminacion de gastos
 *              (RF-09).
 */
#include <stdio.h>
#include "gastos.h"
#include "categorias.h"
#include "utilidades.h"

/*
 * Funcion:     siguienteIdGasto
 * Descripcion: Calcula el id para un gasto nuevo: el mayor id actual mas
 *              1, para no repetir ids aunque se eliminen gastos.
 * Parametros:  gastos    - arreglo de gastos
 *              numGastos - cuantos gastos hay en el arreglo
 * Retorno:     El id disponible (1 si no hay gastos).
 */
static int siguienteIdGasto(const Gasto gastos[], int numGastos) {
    int i = 0;
    int mayor = 0;

    for (i = 0; i < numGastos; i++) {
        if (gastos[i].id > mayor) {
            mayor = gastos[i].id;
        }
    }
    return mayor + 1;
}

/*
 * Funcion:     nombreUsuario
 * Descripcion: Busca el nombre de un usuario por su id.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay
 *              idUsuario   - id a buscar
 * Retorno:     Apuntador al nombre, o "(desconocido)" si no existe.
 */
static const char *nombreUsuario(const Usuario usuarios[], int numUsuarios,
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
 * Funcion:     idsDelGrupo
 * Descripcion: Copia en idsMiembros los ids de los usuarios que
 *              pertenecen al grupo, en el orden de las membresias.
 * Parametros:  miembros    - arreglo de membresias
 *              numMiembros - cuantas membresias hay
 *              idGrupo     - id del grupo
 *              idsMiembros - arreglo de salida (MAX_MIEMBROS lugares)
 * Retorno:     Cuantos miembros se copiaron.
 */
static int idsDelGrupo(const MiembroGrupo miembros[], int numMiembros,
                       int idGrupo, int idsMiembros[]) {
    int i = 0;
    int cuantos = 0;

    for (i = 0; i < numMiembros && cuantos < MAX_MIEMBROS; i++) {
        if (miembros[i].idGrupo == idGrupo) {
            idsMiembros[cuantos] = miembros[i].idUsuario;
            cuantos++;
        }
    }
    return cuantos;
}

/*
 * Funcion:     elegirParticipantes
 * Descripcion: Pide quienes participan en el gasto: todos los miembros
 *              del grupo o algunos elegidos uno por uno. Solo se pueden
 *              elegir miembros del grupo (E3) y no se repiten.
 * Parametros:  usuarios        - arreglo de usuarios (para los nombres)
 *              numUsuarios     - cuantos usuarios hay
 *              idsMiembros     - ids de los miembros del grupo
 *              totalMiembros   - cuantos miembros tiene el grupo
 *              idsParticipantes - arreglo de salida con los ids elegidos
 * Retorno:     Cuantos participantes se eligieron (al menos 1).
 */
static int elegirParticipantes(const Usuario usuarios[], int numUsuarios,
                               const int idsMiembros[], int totalMiembros,
                               int idsParticipantes[]) {
    int elegido[MAX_MIEMBROS] = {0}; /* 1 si el miembro ya se eligio */
    int cuantos = 0;
    int opcion = 0;
    int i = 0;

    printf("Participantes:\n");
    printf("1. Todos los miembros del grupo\n");
    printf("2. Elegir uno por uno\n");
    printf("Opcion: ");
    opcion = leerEntero(1, 2);

    if (opcion == 1) {
        for (i = 0; i < totalMiembros; i++) {
            idsParticipantes[i] = idsMiembros[i];
        }
        return totalMiembros;
    }

    do {
        for (i = 0; i < totalMiembros; i++) {
            printf("%d. %s%s\n", i + 1,
                   nombreUsuario(usuarios, numUsuarios, idsMiembros[i]),
                   elegido[i] ? " (elegido)" : "");
        }
        printf("0. Terminar\n");
        printf("Agrega un participante: ");
        opcion = leerEntero(0, totalMiembros);

        if (opcion == 0 && cuantos == 0) {
            printf("Error: Debe haber al menos un participante.\n");
        } else if (opcion != 0 && elegido[opcion - 1]) {
            printf("Error: Ese miembro ya esta en la lista.\n");
        } else if (opcion != 0) {
            elegido[opcion - 1] = 1;
            idsParticipantes[cuantos] = idsMiembros[opcion - 1];
            cuantos++;
        }
    } while (opcion != 0 || cuantos == 0);

    return cuantos;
}

/*
 * Funcion:     dividirIgual
 * Descripcion: Reparte un monto en centavos en partes iguales. Como no
 *              siempre es exacto, el residuo (los centavos que sobran) se
 *              le asigna al pagador si participa; si no, al primer
 *              participante. Asi la suma de las partes es el total
 *              (RF-07, RNF-04). Ej.: $100.00 entre 3 -> 33.34, 33.33, 33.33.
 * Parametros:  montoCentavos    - total a repartir
 *              idsParticipantes - ids de los participantes
 *              numParticipantes - cuantos participantes hay (> 0)
 *              idPagador        - id del usuario que pago
 *              partes           - arreglo de salida, una parte por
 *                                 participante en el mismo orden
 * Retorno:     Ninguno.
 */
void dividirIgual(long montoCentavos, const int idsParticipantes[],
                  int numParticipantes, int idPagador, long partes[]) {
    long base = 0;
    long residuo = 0;
    int receptor = 0; /* Posicion que recibe el residuo */
    int i = 0;

    base = montoCentavos / numParticipantes;
    residuo = montoCentavos % numParticipantes;

    for (i = 0; i < numParticipantes; i++) {
        partes[i] = base;
        if (idsParticipantes[i] == idPagador) {
            receptor = i;
        }
    }
    partes[receptor] += residuo;
}

/*
 * Funcion:     dividirPersonalizado
 * Descripcion: Pide la parte de cada participante con leerMonto, que
 *              rechaza montos negativos o en cero (E2). Si la suma no es
 *              igual al total, muestra la diferencia y vuelve a pedir
 *              todas las partes (E1) (RF-08, CU-03).
 * Parametros:  montoCentavos    - total del gasto
 *              idsParticipantes - ids de los participantes
 *              numParticipantes - cuantos participantes hay
 *              usuarios         - arreglo de usuarios (para los nombres)
 *              numUsuarios      - cuantos usuarios hay
 *              partes           - arreglo de salida, una parte por
 *                                 participante en el mismo orden
 * Retorno:     Ninguno.
 */
void dividirPersonalizado(long montoCentavos, const int idsParticipantes[],
                          int numParticipantes, const Usuario usuarios[],
                          int numUsuarios, long partes[]) {
    long suma = 0;
    int i = 0;

    do {
        suma = 0;
        printf("Total a repartir: ");
        mostrarMonto(montoCentavos);
        printf("\n");
        for (i = 0; i < numParticipantes; i++) {
            printf("Parte de %s: ",
                   nombreUsuario(usuarios, numUsuarios, idsParticipantes[i]));
            partes[i] = leerMonto();
            suma += partes[i];
        }
        if (suma != montoCentavos) {
            printf("Error: Las partes suman ");
            mostrarMonto(suma);
            printf(" y la diferencia con el total es ");
            mostrarMonto(montoCentavos - suma);
            printf(". Captura las partes de nuevo.\n");
        }
    } while (suma != montoCentavos);
}

/*
 * Funcion:     registrarGasto
 * Descripcion: Captura un gasto del grupo: descripcion, monto (E1),
 *              fecha (E2), categoria, pagador y participantes (E3).
 *              Muestra un resumen y solo guarda si se confirma (E4). Avisa
 *              si ya hay MAX_GASTOS (E5). El monto se divide en partes
 *              iguales o personalizadas y por cada participante se agrega
 *              una DivisionGasto.
 * Parametros:  gastos        - arreglo de gastos
 *              numGastos     - apuntador al contador de gastos
 *              divisiones    - arreglo de divisiones
 *              numDivisiones - apuntador al contador de divisiones
 *              idGrupo       - id del grupo activo
 *              usuarios, numUsuarios     - usuarios del sistema
 *              miembros, numMiembros     - membresias de los grupos
 *              categorias, numCategorias - categorias disponibles
 * Retorno:     1 si se registro, 0 si no.
 */
int registrarGasto(Gasto gastos[], int *numGastos,
                   DivisionGasto divisiones[], int *numDivisiones,
                   int idGrupo,
                   const Usuario usuarios[], int numUsuarios,
                   const MiembroGrupo miembros[], int numMiembros,
                   const Categoria categorias[], int numCategorias) {
    Gasto nuevo;
    int idsMiembros[MAX_MIEMBROS];
    int idsParticipantes[MAX_MIEMBROS];
    long partes[MAX_MIEMBROS]; /* Parte de cada participante, en centavos */
    int totalMiembros = 0;
    int numParticipantes = 0;
    int tipo = 1; /* 1 = partes iguales, 2 = personalizadas */
    int opcion = 0;
    int i = 0;

    if (*numGastos >= MAX_GASTOS) {
        printf("Error: Ya se alcanzo el maximo de %d gastos.\n", MAX_GASTOS);
        return 0;
    }
    totalMiembros = idsDelGrupo(miembros, numMiembros, idGrupo, idsMiembros);
    if (totalMiembros == 0) {
        printf("Error: El grupo no tiene miembros.\n");
        return 0;
    }
    if (numCategorias == 0) {
        printf("Error: No hay categorias registradas.\n");
        return 0;
    }
    if (*numDivisiones + totalMiembros > MAX_DIVISIONES) {
        printf("Error: Ya no caben mas divisiones de gastos.\n");
        return 0;
    }

    printf("\n--- Registrar gasto ---\n");
    printf("Descripcion: ");
    leerTexto(nuevo.descripcion, LONG_DESCRIPCION + 1);
    printf("Monto (por ejemplo 840.50): ");
    nuevo.montoCentavos = leerMonto();
    printf("Fecha (dd/mm/aaaa): ");
    nuevo.fecha = leerFecha();

    printf("Categoria:\n");
    listarCategorias(categorias, numCategorias);
    printf("Elige la categoria: ");
    nuevo.idCategoria = categorias[leerEntero(1, numCategorias) - 1].id;

    printf("Quien pago:\n");
    for (i = 0; i < totalMiembros; i++) {
        printf("%d. %s\n", i + 1,
               nombreUsuario(usuarios, numUsuarios, idsMiembros[i]));
    }
    printf("Elige al pagador: ");
    nuevo.idPagador = idsMiembros[leerEntero(1, totalMiembros) - 1];

    numParticipantes = elegirParticipantes(usuarios, numUsuarios, idsMiembros,
                                           totalMiembros, idsParticipantes);

    /* Con un solo participante no hay nada que elegir */
    if (numParticipantes > 1) {
        printf("Como se divide el gasto:\n");
        printf("1. Partes iguales\n");
        printf("2. Partes personalizadas\n");
        printf("Opcion: ");
        tipo = leerEntero(1, 2);
    }
    if (tipo == 1) {
        nuevo.tipoDivision = DIVISION_IGUAL;
        dividirIgual(nuevo.montoCentavos, idsParticipantes, numParticipantes,
                     nuevo.idPagador, partes);
    } else {
        nuevo.tipoDivision = DIVISION_PERSONALIZADA;
        dividirPersonalizado(nuevo.montoCentavos, idsParticipantes,
                             numParticipantes, usuarios, numUsuarios, partes);
    }

    /* Resumen antes de guardar (E4) */
    printf("\n--- Resumen ---\n");
    printf("Descripcion:   %s\n", nuevo.descripcion);
    printf("Monto:         ");
    mostrarMonto(nuevo.montoCentavos);
    printf("\nFecha:         %02d/%02d/%04d\n", nuevo.fecha % 100,
           (nuevo.fecha / 100) % 100, nuevo.fecha / 10000);
    printf("Pago:          %s\n",
           nombreUsuario(usuarios, numUsuarios, nuevo.idPagador));
    printf("Division en partes %s:\n",
           (nuevo.tipoDivision == DIVISION_IGUAL) ? "iguales" : "personalizadas");
    for (i = 0; i < numParticipantes; i++) {
        printf("  %-20s ", nombreUsuario(usuarios, numUsuarios,
                                          idsParticipantes[i]));
        mostrarMonto(partes[i]);
        printf("\n");
    }
    printf("Guardar el gasto (1 = si, 0 = cancelar): ");
    opcion = leerEntero(0, 1);
    if (opcion == 0) {
        printf("Gasto cancelado; no se guardo nada.\n");
        return 0;
    }

    nuevo.id = siguienteIdGasto(gastos, *numGastos);
    nuevo.idGrupo = idGrupo;
    gastos[*numGastos] = nuevo;
    (*numGastos)++;

    /* Una division por participante con la parte que le toca */
    for (i = 0; i < numParticipantes; i++) {
        divisiones[*numDivisiones].idGasto = nuevo.id;
        divisiones[*numDivisiones].idUsuario = idsParticipantes[i];
        divisiones[*numDivisiones].montoCentavos = partes[i];
        (*numDivisiones)++;
    }

    printf("Gasto registrado.\n");
    return 1;
}

/*
 * Funcion:     listarGastosGrupo
 * Descripcion: Muestra con un numero los gastos del grupo (fecha,
 *              descripcion, monto y quien pago) y guarda en posiciones la
 *              posicion de cada uno en el arreglo de gastos.
 * Parametros:  gastos      - arreglo de gastos
 *              numGastos   - cuantos gastos hay
 *              idGrupo     - id del grupo
 *              usuarios    - arreglo de usuarios (para los nombres)
 *              numUsuarios - cuantos usuarios hay
 *              posiciones  - arreglo de salida (MAX_GASTOS lugares)
 * Retorno:     Cuantos gastos se mostraron.
 */
static int listarGastosGrupo(const Gasto gastos[], int numGastos, int idGrupo,
                             const Usuario usuarios[], int numUsuarios,
                             int posiciones[]) {
    int i = 0;
    int cuantos = 0;

    for (i = 0; i < numGastos; i++) {
        if (gastos[i].idGrupo == idGrupo) {
            posiciones[cuantos] = i;
            cuantos++;
            printf("%d. %02d/%02d/%04d  %-25s ", cuantos,
                   gastos[i].fecha % 100, (gastos[i].fecha / 100) % 100,
                   gastos[i].fecha / 10000, gastos[i].descripcion);
            mostrarMonto(gastos[i].montoCentavos);
            printf("  (pago %s)\n",
                   nombreUsuario(usuarios, numUsuarios, gastos[i].idPagador));
        }
    }
    return cuantos;
}

/*
 * Funcion:     eliminarGasto
 * Descripcion: Muestra los gastos del grupo, pide elegir uno, revisa que
 *              el usuario sea quien lo pago o el Administrador, pide
 *              confirmacion y lo elimina junto con sus divisiones
 *              (RF-09). Los elementos siguientes se recorren una posicion.
 * Parametros:  gastos        - arreglo de gastos
 *              numGastos     - apuntador al contador de gastos
 *              divisiones    - arreglo de divisiones
 *              numDivisiones - apuntador al contador de divisiones
 *              idGrupo       - id del grupo activo
 *              usuario       - usuario que inicio sesion
 *              usuarios      - arreglo de usuarios (para los nombres)
 *              numUsuarios   - cuantos usuarios hay
 * Retorno:     1 si se elimino, 0 si no.
 */
int eliminarGasto(Gasto gastos[], int *numGastos,
                  DivisionGasto divisiones[], int *numDivisiones,
                  int idGrupo, const Usuario *usuario,
                  const Usuario usuarios[], int numUsuarios) {
    int posiciones[MAX_GASTOS]; /* Posicion de cada gasto que se muestra */
    int cuantos = 0;
    int opcion = 0;
    int posicion = 0;
    int idGasto = 0;
    int i = 0;
    int j = 0;

    printf("\n--- Eliminar gasto ---\n");
    cuantos = listarGastosGrupo(gastos, *numGastos, idGrupo, usuarios,
                                numUsuarios, posiciones);
    if (cuantos == 0) {
        printf("No hay gastos registrados en el grupo.\n");
        return 0;
    }
    printf("0. Cancelar\n");
    printf("Elige el gasto: ");
    opcion = leerEntero(0, cuantos);
    if (opcion == 0) {
        return 0;
    }
    posicion = posiciones[opcion - 1];

    if (!usuario->esAdministrador &&
        gastos[posicion].idPagador != usuario->id) {
        printf("Error: Solo quien pago el gasto o el Administrador puede "
               "eliminarlo.\n");
        return 0;
    }

    printf("Se eliminara \"%s\". Confirmar (1 = si, 0 = no): ",
           gastos[posicion].descripcion);
    if (leerEntero(0, 1) == 0) {
        printf("No se elimino el gasto.\n");
        return 0;
    }

    idGasto = gastos[posicion].id;

    /* Recorre los gastos siguientes una posicion a la izquierda */
    for (i = posicion; i < *numGastos - 1; i++) {
        gastos[i] = gastos[i + 1];
    }
    (*numGastos)--;

    /* Quita las divisiones del gasto, conservando las demas en orden */
    for (i = 0; i < *numDivisiones; i++) {
        if (divisiones[i].idGasto != idGasto) {
            divisiones[j] = divisiones[i];
            j++;
        }
    }
    *numDivisiones = j;

    printf("Gasto eliminado.\n");
    return 1;
}
