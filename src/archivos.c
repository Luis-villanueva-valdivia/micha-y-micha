/*
 * Archivo:     archivos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.1
 * Descripcion: Implementacion del guardado y la carga de datos en archivos
 *              de texto con campos separados por '|' (RF-16, RF-17).
 */
#include <stdio.h>
#include <string.h>
#include "archivos.h"

/*
 * Funcion:     guardarUsuarios
 * Descripcion: Escribe todos los usuarios en ARCHIVO_USUARIOS, uno por
 *              linea con el formato id|nombre|pin|esAdministrador. Si el
 *              archivo ya existia, se reemplaza.
 * Parametros:  usuarios    - arreglo de usuarios a guardar (entrada)
 *              numUsuarios - cuantos usuarios hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarUsuarios(const Usuario usuarios[], int numUsuarios) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numUsuarios; i++) {
        fprintf(archivo, "%d|%s|%s|%d\n", usuarios[i].id, usuarios[i].nombre,
                usuarios[i].pin, usuarios[i].esAdministrador);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarUsuarios
 * Descripcion: Lee los usuarios de ARCHIVO_USUARIOS (una linea por
 *              usuario, campos separados por '|') y los guarda en el
 *              arreglo. Las lineas danadas se ignoran. Lee como maximo
 *              MAX_USUARIOS.
 * Parametros:  usuarios    - arreglo donde se guardan (salida)
 *              numUsuarios - cuantos usuarios se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no existe o no se
 *              pudo abrir (en ese caso *numUsuarios queda en 0).
 */
int cargarUsuarios(Usuario usuarios[], int *numUsuarios) {
    FILE *archivo = NULL;
    char linea[100];
    Usuario leido;
    int campos = 0;

    *numUsuarios = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numUsuarios < MAX_USUARIOS) {
         /* Los anchos 30 y 4 deben coincidir con LONG_NOMBRE y LONG_PIN */
        campos = sscanf(linea, "%d|%30[^|]|%4[^|]|%d", &leido.id, leido.nombre,
                        leido.pin, &leido.esAdministrador);
        if (campos == 4) {
            usuarios[*numUsuarios] = leido;
            (*numUsuarios)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarGrupos
 * Descripcion: Escribe todos los grupos en ARCHIVO_GRUPOS, uno por linea
 *              con el formato id|nombre|idAdministrador.
 * Parametros:  grupos    - arreglo de grupos a guardar (entrada)
 *              numGrupos - cuantos grupos hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarGrupos(const Grupo grupos[], int numGrupos) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_GRUPOS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numGrupos; i++) {
        fprintf(archivo, "%d|%s|%d\n", grupos[i].id, grupos[i].nombre,
                grupos[i].idAdministrador);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarGrupos
 * Descripcion: Lee los grupos de ARCHIVO_GRUPOS. Las lineas danadas se
 *              ignoran. Lee como maximo MAX_GRUPOS.
 * Parametros:  grupos    - arreglo donde se guardan (salida)
 *              numGrupos - cuantos grupos se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numGrupos en 0).
 */
int cargarGrupos(Grupo grupos[], int *numGrupos) {
    FILE *archivo = NULL;
    char linea[100];
    Grupo leido;
    int campos = 0;

    *numGrupos = 0;

    archivo = fopen(ARCHIVO_GRUPOS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numGrupos < MAX_GRUPOS) {
        /* El ancho 30 debe coincidir con LONG_NOMBRE */
        campos = sscanf(linea, "%d|%30[^|]|%d", &leido.id, leido.nombre,
                        &leido.idAdministrador);
        if (campos == 3) {
            grupos[*numGrupos] = leido;
            (*numGrupos)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarMiembros
 * Descripcion: Escribe todas las membresias en ARCHIVO_MIEMBROS, una por
 *              linea con el formato idGrupo|idUsuario.
 * Parametros:  miembros    - arreglo de membresias a guardar (entrada)
 *              numMiembros - cuantas membresias hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarMiembros(const MiembroGrupo miembros[], int numMiembros) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_MIEMBROS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numMiembros; i++) {
        fprintf(archivo, "%d|%d\n", miembros[i].idGrupo, miembros[i].idUsuario);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarMiembros
 * Descripcion: Lee las membresias de ARCHIVO_MIEMBROS. Las lineas danadas
 *              se ignoran. Lee como maximo MAX_MEMBRESIAS.
 * Parametros:  miembros    - arreglo donde se guardan (salida)
 *              numMiembros - cuantas membresias se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numMiembros en 0).
 */
int cargarMiembros(MiembroGrupo miembros[], int *numMiembros) {
    FILE *archivo = NULL;
    char linea[100];
    MiembroGrupo leido;
    int campos = 0;

    *numMiembros = 0;

    archivo = fopen(ARCHIVO_MIEMBROS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numMiembros < MAX_MEMBRESIAS) {
        campos = sscanf(linea, "%d|%d", &leido.idGrupo, &leido.idUsuario);
        if (campos == 2) {
            miembros[*numMiembros] = leido;
            (*numMiembros)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarCategorias
 * Descripcion: Escribe todas las categorias en ARCHIVO_CATEGORIAS, una por
 *              linea con el formato id|nombre.
 * Parametros:  categorias    - arreglo de categorias a guardar (entrada)
 *              numCategorias - cuantas categorias hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarCategorias(const Categoria categorias[], int numCategorias) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_CATEGORIAS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numCategorias; i++) {
        fprintf(archivo, "%d|%s\n", categorias[i].id, categorias[i].nombre);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarCategorias
 * Descripcion: Lee las categorias de ARCHIVO_CATEGORIAS. Las lineas
 *              danadas se ignoran. Lee como maximo MAX_CATEGORIAS.
 * Parametros:  categorias    - arreglo donde se guardan (salida)
 *              numCategorias - cuantas categorias se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numCategorias
 *              en 0).
 */
int cargarCategorias(Categoria categorias[], int *numCategorias) {
    FILE *archivo = NULL;
    char linea[100];
    Categoria leido;
    int campos = 0;

    *numCategorias = 0;

    archivo = fopen(ARCHIVO_CATEGORIAS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numCategorias < MAX_CATEGORIAS) {
        /* El ancho 30 debe coincidir con LONG_NOMBRE */
        campos = sscanf(linea, "%d|%30[^\n]", &leido.id, leido.nombre);
        if (campos == 2) {
            categorias[*numCategorias] = leido;
            (*numCategorias)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarGastos
 * Descripcion: Escribe todos los gastos en ARCHIVO_GASTOS, uno por linea
 *              con el formato id|idGrupo|idPagador|idCategoria|
 *              descripcion|montoCentavos|fecha|tipoDivision.
 * Parametros:  gastos    - arreglo de gastos a guardar (entrada)
 *              numGastos - cuantos gastos hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarGastos(const Gasto gastos[], int numGastos) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_GASTOS, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numGastos; i++) {
        fprintf(archivo, "%d|%d|%d|%d|%s|%ld|%d|%d\n", gastos[i].id,
                gastos[i].idGrupo, gastos[i].idPagador, gastos[i].idCategoria,
                gastos[i].descripcion, gastos[i].montoCentavos, gastos[i].fecha,
                (int)gastos[i].tipoDivision);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarGastos
 * Descripcion: Lee los gastos de ARCHIVO_GASTOS. Las lineas danadas se
 *              ignoran. Lee como maximo MAX_GASTOS.
 * Parametros:  gastos    - arreglo donde se guardan (salida)
 *              numGastos - cuantos gastos se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numGastos en 0).
 */
int cargarGastos(Gasto gastos[], int *numGastos) {
    FILE *archivo = NULL;
    char linea[200];
    Gasto leido;
    int tipo = 0; /* temporal para leer el enum tipoDivision */
    int campos = 0;

    *numGastos = 0;

    archivo = fopen(ARCHIVO_GASTOS, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numGastos < MAX_GASTOS) {
        /* El ancho 50 debe coincidir con LONG_DESCRIPCION */
        campos = sscanf(linea, "%d|%d|%d|%d|%50[^|]|%ld|%d|%d", &leido.id,
                        &leido.idGrupo, &leido.idPagador, &leido.idCategoria,
                        leido.descripcion, &leido.montoCentavos, &leido.fecha,
                        &tipo);
        if (campos == 8) {
            leido.tipoDivision = (TipoDivision)tipo;
            gastos[*numGastos] = leido;
            (*numGastos)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarDivisiones
 * Descripcion: Escribe todas las divisiones en ARCHIVO_DIVISIONES, una
 *              por linea con el formato idGasto|idUsuario|montoCentavos.
 * Parametros:  divisiones    - arreglo de divisiones a guardar (entrada)
 *              numDivisiones - cuantas divisiones hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarDivisiones(const DivisionGasto divisiones[], int numDivisiones) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_DIVISIONES, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numDivisiones; i++) {
        fprintf(archivo, "%d|%d|%ld\n", divisiones[i].idGasto,
                divisiones[i].idUsuario, divisiones[i].montoCentavos);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarDivisiones
 * Descripcion: Lee las divisiones de ARCHIVO_DIVISIONES. Las lineas
 *              danadas se ignoran. Lee como maximo MAX_DIVISIONES.
 * Parametros:  divisiones    - arreglo donde se guardan (salida)
 *              numDivisiones - cuantas divisiones se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y *numDivisiones
 *              en 0).
 */
int cargarDivisiones(DivisionGasto divisiones[], int *numDivisiones) {
    FILE *archivo = NULL;
    char linea[100];
    DivisionGasto leido;
    int campos = 0;

    *numDivisiones = 0;

    archivo = fopen(ARCHIVO_DIVISIONES, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numDivisiones < MAX_DIVISIONES) {
        campos = sscanf(linea, "%d|%d|%ld", &leido.idGasto, &leido.idUsuario,
                        &leido.montoCentavos);
        if (campos == 3) {
            divisiones[*numDivisiones] = leido;
            (*numDivisiones)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     guardarLiquidaciones
 * Descripcion: Escribe todas las liquidaciones en ARCHIVO_LIQUIDACIONES,
 *              una por linea con el formato id|idGrupo|idDeudor|
 *              idAcreedor|montoCentavos|fecha.
 * Parametros:  liquidaciones    - arreglo de liquidaciones (entrada)
 *              numLiquidaciones - cuantas liquidaciones hay en el arreglo
 * Retorno:     1 si se guardo bien, 0 si no se pudo abrir el archivo.
 */
int guardarLiquidaciones(const Liquidacion liquidaciones[],
                         int numLiquidaciones) {
    FILE *archivo = NULL;
    int i = 0;

    archivo = fopen(ARCHIVO_LIQUIDACIONES, "w");
    if (archivo == NULL) {
        return 0;
    }

    for (i = 0; i < numLiquidaciones; i++) {
        fprintf(archivo, "%d|%d|%d|%d|%ld|%d\n", liquidaciones[i].id,
                liquidaciones[i].idGrupo, liquidaciones[i].idDeudor,
                liquidaciones[i].idAcreedor, liquidaciones[i].montoCentavos,
                liquidaciones[i].fecha);
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     cargarLiquidaciones
 * Descripcion: Lee las liquidaciones de ARCHIVO_LIQUIDACIONES. Las lineas
 *              danadas se ignoran. Lee como maximo MAX_LIQUIDACIONES.
 * Parametros:  liquidaciones    - arreglo donde se guardan (salida)
 *              numLiquidaciones - cuantas se leyeron (salida)
 * Retorno:     1 si se pudo abrir el archivo, 0 si no (y
 *              *numLiquidaciones en 0).
 */
int cargarLiquidaciones(Liquidacion liquidaciones[], int *numLiquidaciones) {
    FILE *archivo = NULL;
    char linea[100];
    Liquidacion leido;
    int campos = 0;

    *numLiquidaciones = 0;

    archivo = fopen(ARCHIVO_LIQUIDACIONES, "r");
    if (archivo == NULL) {
        return 0;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL &&
           *numLiquidaciones < MAX_LIQUIDACIONES) {
        campos = sscanf(linea, "%d|%d|%d|%d|%ld|%d", &leido.id,
                        &leido.idGrupo, &leido.idDeudor, &leido.idAcreedor,
                        &leido.montoCentavos, &leido.fecha);
        if (campos == 6) {
            liquidaciones[*numLiquidaciones] = leido;
            (*numLiquidaciones)++;
        }
    }

    fclose(archivo);
    return 1;
}

/*
 * Funcion:     crearCategoriasPredeterminadas
 * Descripcion: Llena el arreglo con las cinco categorias predeterminadas
 *              (Renta, Servicios, Super, Limpieza, Otros) con ids del 1 al
 *              5 y las guarda en ARCHIVO_CATEGORIAS. Se usa cuando el
 *              archivo de categorias no existe.
 * Parametros:  categorias    - arreglo donde se crean (salida)
 *              numCategorias - cuantas categorias quedaron (salida)
 * Retorno:     1 si se guardaron bien, 0 si no se pudo escribir el archivo.
 */
int crearCategoriasPredeterminadas(Categoria categorias[],int *numCategorias) {
    const char *nombres[] = {"Renta", "Servicios", "Super", "Limpieza", "Otros"};
    int totalNombres = 5;
    int i = 0;

    for (i = 0; i < totalNombres; i++) {
        categorias[i].id = i + 1;
        strcpy(categorias[i].nombre, nombres[i]);
    }
    *numCategorias = totalNombres;

    return guardarCategorias(categorias, *numCategorias);
}