/*
 * Archivo:     categorias.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.2
 * Descripcion: Implementacion de la gestion de categorias: listar,
 *              agregar, renombrar y eliminar (RF-05, CU-11).
 */
#include <stdio.h>
#include <string.h>
#include "categorias.h"
#include "utilidades.h"

/*
 * Funcion:     existeNombreCategoria
 * Descripcion: Revisa si ya hay una categoria con ese nombre, sin contar
 *              la de la posicion ignorar (sirve al renombrar).
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay en el arreglo
 *              nombre        - nombre a buscar
 *              ignorar       - posicion que no se compara, o -1
 * Retorno:     1 si el nombre ya existe, 0 si no.
 */
static int existeNombreCategoria(const Categoria categorias[],
                                 int numCategorias, const char *nombre,
                                 int ignorar) {
    int i = 0;

    for (i = 0; i < numCategorias; i++) {
        if (i != ignorar && strcmp(categorias[i].nombre, nombre) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * Funcion:     siguienteIdCategoria
 * Descripcion: Calcula el id para una categoria nueva: el mayor id
 *              actual mas 1, para no repetir ids aunque se eliminen.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay en el arreglo
 * Retorno:     El id disponible (1 si no hay categorias).
 */
static int siguienteIdCategoria(const Categoria categorias[],
                                int numCategorias) {
    int i = 0;
    int mayor = 0;

    for (i = 0; i < numCategorias; i++) {
        if (categorias[i].id > mayor) {
            mayor = categorias[i].id;
        }
    }
    return mayor + 1;
}

/*
 * Funcion:     listarCategorias
 * Descripcion: Muestra cada categoria con un numero para elegirla (1, 2,
 *              3...) y su nombre.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay en el arreglo
 * Retorno:     Ninguno.
 */
void listarCategorias(const Categoria categorias[], int numCategorias) {
    int i = 0;

    for (i = 0; i < numCategorias; i++) {
        printf("%d. %s\n", i + 1, categorias[i].nombre);
    }
}

/*
 * Funcion:     buscarCategoriaPorId
 * Descripcion: Busca una categoria por su id.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay en el arreglo
 *              idCategoria   - id a buscar
 * Retorno:     La posicion de la categoria, o -1 si no existe.
 */
int buscarCategoriaPorId(const Categoria categorias[], int numCategorias,
                         int idCategoria) {
    int i = 0;

    for (i = 0; i < numCategorias; i++) {
        if (categorias[i].id == idCategoria) {
            return i;
        }
    }
    return -1;
}

/*
 * Funcion:     agregarCategoria
 * Descripcion: Pide el nombre de una categoria nueva y la agrega al
 *              arreglo. Rechaza nombres repetidos (E1) y avisa si ya hay
 *              MAX_CATEGORIAS. El nombre vacio lo rechaza leerTexto.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - apuntador al contador; aumenta en 1 si se
 *                              agrega
 * Retorno:     1 si se agrego, 0 si no.
 */
int agregarCategoria(Categoria categorias[], int *numCategorias) {
    Categoria nueva;

    if (*numCategorias >= MAX_CATEGORIAS) {
        printf("Error: Ya se alcanzo el maximo de %d categorias.\n",
               MAX_CATEGORIAS);
        return 0;
    }

    printf("Nombre de la categoria: ");
    leerTexto(nueva.nombre, LONG_NOMBRE + 1);

    if (existeNombreCategoria(categorias, *numCategorias, nueva.nombre, -1)) {
        printf("Error: Ya existe una categoria con ese nombre.\n");
        return 0;
    }

    nueva.id = siguienteIdCategoria(categorias, *numCategorias);
    categorias[*numCategorias] = nueva;
    (*numCategorias)++;

    printf("Categoria \"%s\" agregada.\n", nueva.nombre);
    return 1;
}

/*
 * Funcion:     elegirCategoria
 * Descripcion: Muestra la lista de categorias y pide elegir una. La
 *              opcion 0 cancela.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay en el arreglo
 * Retorno:     La posicion elegida, o -1 si se cancelo o no hay.
 */
static int elegirCategoria(const Categoria categorias[], int numCategorias) {
    int opcion = 0;

    if (numCategorias == 0) {
        printf("No hay categorias registradas.\n");
        return -1;
    }
    listarCategorias(categorias, numCategorias);
    printf("0. Cancelar\n");
    printf("Elige la categoria: ");
    opcion = leerEntero(0, numCategorias);
    return opcion - 1; /* 0 se convierte en -1 (cancelar) */
}

/*
 * Funcion:     renombrarCategoria
 * Descripcion: Pide elegir una categoria y le cambia el nombre. Rechaza
 *              nombres repetidos (E1).
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - cuantas categorias hay en el arreglo
 * Retorno:     1 si se renombro, 0 si no.
 */
int renombrarCategoria(Categoria categorias[], int numCategorias) {
    char nombre[LONG_NOMBRE + 1];
    int posicion = 0;

    posicion = elegirCategoria(categorias, numCategorias);
    if (posicion == -1) {
        return 0;
    }

    printf("Nuevo nombre: ");
    leerTexto(nombre, LONG_NOMBRE + 1);

    if (existeNombreCategoria(categorias, numCategorias, nombre, posicion)) {
        printf("Error: Ya existe una categoria con ese nombre.\n");
        return 0;
    }

    strcpy(categorias[posicion].nombre, nombre);
    printf("Categoria renombrada.\n");
    return 1;
}

/*
 * Funcion:     eliminarCategoria
 * Descripcion: Pide elegir una categoria y la elimina, siempre que ningun
 *              gasto la use (E2). Las siguientes se recorren una posicion.
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - apuntador al contador de categorias
 *              gastos        - arreglo de gastos, para revisar su uso
 *              numGastos     - cuantos gastos hay en el arreglo
 * Retorno:     1 si se elimino, 0 si no.
 */
int eliminarCategoria(Categoria categorias[], int *numCategorias,
                      const Gasto gastos[], int numGastos) {
    int posicion = 0;
    int i = 0;

    posicion = elegirCategoria(categorias, *numCategorias);
    if (posicion == -1) {
        return 0;
    }

    for (i = 0; i < numGastos; i++) {
        if (gastos[i].idCategoria == categorias[posicion].id) {
            printf("Error: La categoria tiene gastos asociados; no se puede "
                   "eliminar.\n");
            return 0;
        }
    }

    for (i = posicion; i < *numCategorias - 1; i++) {
        categorias[i] = categorias[i + 1];
    }
    (*numCategorias)--;

    printf("Categoria eliminada.\n");
    return 1;
}
