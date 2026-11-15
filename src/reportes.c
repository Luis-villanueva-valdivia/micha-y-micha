/*
 * Archivo:     reportes.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     1.0
 * Descripcion: Implementacion de los reportes. Los ordenamientos se
 *              hacen sobre arreglos de indices para no cambiar el orden de
 *              los datos originales (RF-13, RF-14, CU-07, CU-08).
 */
#include <stdio.h>
#include "reportes.h"
#include "utilidades.h"

/*
 * Funcion:     nombreUsuarioRep
 * Descripcion: Busca el nombre de un usuario por su id.
 * Parametros:  usuarios    - arreglo de usuarios
 *              numUsuarios - cuantos usuarios hay
 *              idUsuario   - id a buscar
 * Retorno:     Apuntador al nombre, o "(desconocido)" si no existe.
 */
static const char *nombreUsuarioRep(const Usuario usuarios[], int numUsuarios,
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
 * Funcion:     nombreCategoria
 * Descripcion: Busca el nombre de una categoria por su id.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay
 *              idCategoria   - id a buscar
 * Retorno:     Apuntador al nombre, o "(sin categoria)" si no existe.
 */
static const char *nombreCategoria(const Categoria categorias[],
                                   int numCategorias, int idCategoria) {
    int i = 0;

    for (i = 0; i < numCategorias; i++) {
        if (categorias[i].id == idCategoria) {
            return categorias[i].nombre;
        }
    }
    return "(sin categoria)";
}

/*
 * Funcion:     indicesDelGrupo
 * Descripcion: Copia en indices la posicion de cada gasto del grupo. Si
 *              mes y anio son distintos de 0, solo copia los de ese mes.
 * Parametros:  gastos    - arreglo de gastos
 *              numGastos - cuantos gastos hay
 *              idGrupo   - id del grupo
 *              mes       - mes a filtrar (1-12), o 0 para todos
 *              anio      - anio a filtrar, o 0 para todos
 *              indices   - arreglo de salida (MAX_GASTOS lugares)
 * Retorno:     Cuantos gastos se copiaron.
 */
static int indicesDelGrupo(const Gasto gastos[], int numGastos, int idGrupo,
                           int mes, int anio, int indices[]) {
    int i = 0;
    int cuantos = 0;

    for (i = 0; i < numGastos; i++) {
        if (gastos[i].idGrupo != idGrupo) {
            continue;
        }
        /* La fecha se guarda como aaaammdd */
        if (mes != 0 && ((gastos[i].fecha / 100) % 100 != mes ||
                         gastos[i].fecha / 10000 != anio)) {
            continue;
        }
        indices[cuantos] = i;
        cuantos++;
    }
    return cuantos;
}

/*
 * Funcion:     pedirPeriodo
 * Descripcion: Pregunta si el reporte es de todos los gastos o de un solo
 *              mes y, en ese caso, pide el mes y el anio.
 * Parametros:  mes  - apuntador donde se deja el mes (0 = todos)
 *              anio - apuntador donde se deja el anio (0 = todos)
 * Retorno:     Ninguno.
 */
static void pedirPeriodo(int *mes, int *anio) {
    *mes = 0;
    *anio = 0;
    printf("1. Todos los gastos\n");
    printf("2. Solo un mes\n");
    printf("Opcion: ");
    if (leerEntero(1, 2) == 2) {
        printf("Mes (1-12): ");
        *mes = leerEntero(1, 12);
        printf("Anio (por ejemplo 2026): ");
        *anio = leerEntero(2000, 2100);
    }
}

/*
 * Funcion:     ordenarPorFecha
 * Descripcion: Ordena los indices por fecha del gasto, de la mas
 *              reciente a la mas antigua, con el metodo de seleccion.
 *              Solo se mueven los indices; los gastos no cambian.
 * Parametros:  gastos  - arreglo de gastos
 *              indices - posiciones de los gastos a ordenar
 *              n       - cuantos indices hay
 * Retorno:     Ninguno.
 */
static void ordenarPorFecha(const Gasto gastos[], int indices[], int n) {
    int i = 0;
    int j = 0;
    int mayor = 0;
    int temporal = 0;

    for (i = 0; i < n - 1; i++) {
        mayor = i;
        for (j = i + 1; j < n; j++) {
            if (gastos[indices[j]].fecha > gastos[indices[mayor]].fecha) {
                mayor = j;
            }
        }
        if (mayor != i) {
            temporal = indices[i];
            indices[i] = indices[mayor];
            indices[mayor] = temporal;
        }
    }
}

/*
 * Funcion:     mostrarHistorial
 * Descripcion: Pregunta si se quiere ver todo el historial o solo un mes,
 *              y muestra los gastos del grupo ordenados del mas reciente
 *              al mas antiguo con fecha, descripcion, categoria, quien
 *              pago y monto. Al final muestra el total (RF-13, CU-07).
 * Parametros:  idGrupo                   - id del grupo activo
 *              gastos, numGastos         - gastos del sistema
 *              usuarios, numUsuarios     - usuarios (para los nombres)
 *              categorias, numCategorias - categorias (para los nombres)
 * Retorno:     Ninguno.
 */
void mostrarHistorial(int idGrupo,
                      const Gasto gastos[], int numGastos,
                      const Usuario usuarios[], int numUsuarios,
                      const Categoria categorias[], int numCategorias) {
    int indices[MAX_GASTOS];
    int cuantos = 0;
    int mes = 0;
    int anio = 0;
    long total = 0;
    int i = 0;
    int k = 0;

    printf("\n--- Historial de gastos ---\n");
    pedirPeriodo(&mes, &anio);

    cuantos = indicesDelGrupo(gastos, numGastos, idGrupo, mes, anio, indices);
    if (cuantos == 0) {
        printf("No hay gastos para mostrar.\n");
        return;
    }
    ordenarPorFecha(gastos, indices, cuantos);

    printf("%-10s  %-22s  %-12s  %-12s  %10s\n", "Fecha", "Descripcion",
           "Categoria", "Pago", "Monto");
    for (i = 0; i < cuantos; i++) {
        k = indices[i];
        printf("%02d/%02d/%04d  %-22.22s  %-12.12s  %-12.12s  ",
               gastos[k].fecha % 100, (gastos[k].fecha / 100) % 100,
               gastos[k].fecha / 10000, gastos[k].descripcion,
               nombreCategoria(categorias, numCategorias,
                               gastos[k].idCategoria),
               nombreUsuarioRep(usuarios, numUsuarios, gastos[k].idPagador));
        mostrarMonto(gastos[k].montoCentavos);
        printf("\n");
        total += gastos[k].montoCentavos;
    }
    printf("Total de %d gasto(s): ", cuantos);
    mostrarMonto(total);
    printf("\n");
}

/*
 * Funcion:     reportePorCategoria
 * Descripcion: Suma los gastos del grupo (todos o de un mes) por
 *              categoria y muestra, de la mayor a la menor, la cantidad de
 *              gastos, el monto, el porcentaje del total con un decimal y
 *              una barra de asteriscos proporcional (30 = 100 %). El
 *              porcentaje se calcula con enteros en centavos, redondeando
 *              (RF-14, CU-08).
 * Parametros:  idGrupo                   - id del grupo activo
 *              gastos, numGastos         - gastos del sistema
 *              categorias, numCategorias - categorias del sistema
 * Retorno:     Ninguno.
 */
void reportePorCategoria(int idGrupo,
                         const Gasto gastos[], int numGastos,
                         const Categoria categorias[], int numCategorias) {
    int indices[MAX_GASTOS];
    long totales[MAX_CATEGORIAS]; /* Monto por categoria, mismo orden */
    int cuenta[MAX_CATEGORIAS];   /* Gastos por categoria, mismo orden */
    int orden[MAX_CATEGORIAS];    /* Categorias con gastos, para ordenar */
    int numOrden = 0;
    int numIndices = 0;
    long total = 0;
    long decimas = 0;
    int asteriscos = 0;
    int mes = 0;
    int anio = 0;
    int mayor = 0;
    int temporal = 0;
    int i = 0;
    int j = 0;
    int c = 0;

    printf("\n--- Gastos por categoria ---\n");
    pedirPeriodo(&mes, &anio);

    numIndices = indicesDelGrupo(gastos, numGastos, idGrupo, mes, anio,
                                 indices);
    if (numIndices == 0) {
        printf("No hay gastos para mostrar.\n");
        return;
    }

    for (c = 0; c < numCategorias; c++) {
        totales[c] = 0;
        cuenta[c] = 0;
    }
    for (i = 0; i < numIndices; i++) {
        for (c = 0; c < numCategorias; c++) {
            if (categorias[c].id == gastos[indices[i]].idCategoria) {
                totales[c] += gastos[indices[i]].montoCentavos;
                cuenta[c]++;
                break;
            }
        }
        total += gastos[indices[i]].montoCentavos;
    }

    /* Solo las categorias con gastos, ordenadas de mayor a menor monto
       con el metodo de seleccion */
    for (c = 0; c < numCategorias; c++) {
        if (cuenta[c] > 0) {
            orden[numOrden] = c;
            numOrden++;
        }
    }
    for (i = 0; i < numOrden - 1; i++) {
        mayor = i;
        for (j = i + 1; j < numOrden; j++) {
            if (totales[orden[j]] > totales[orden[mayor]]) {
                mayor = j;
            }
        }
        temporal = orden[i];
        orden[i] = orden[mayor];
        orden[mayor] = temporal;
    }

    printf("%-15s  %6s  %12s  %6s\n", "Categoria", "Gastos", "Monto", "%");
    for (i = 0; i < numOrden; i++) {
        c = orden[i];
        decimas = (totales[c] * 1000 + total / 2) / total;
        asteriscos = (int)((totales[c] * 30 + total / 2) / total);
        printf("%-15.15s  %6d  ", categorias[c].nombre, cuenta[c]);
        mostrarMonto(totales[c]);
        printf("  %3ld.%ld  ", decimas / 10, decimas % 10);
        for (j = 0; j < asteriscos; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("Total: ");
    mostrarMonto(total);
    printf("\n");
}
