/*
 * Archivo:     main.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.2
 * Descripcion: Punto de entrada y menu principal. Cada opcion llama a
 *              una funcion de su modulo; aqui no va logica de negocio.
 */
#include <stdio.h>
#include "estructuras.h"
#include "archivos.h"
#include "usuarios.h"
#include "utilidades.h"

/*
 * Funcion:     mostrarMenuPrincipal
 * Descripcion: Imprime el menu principal con el grupo activo y, si el
 *              usuario es Administrador, la marca [Admin] (RNF-02).
 * Parametros:  usuarios      - arreglo de usuarios
 *              usuarioActivo - posicion del usuario que inicio sesion
 *              grupos        - arreglo de grupos
 *              grupoActivo   - posicion del grupo activo, o -1 si no hay
 * Retorno:     Ninguno.
 */
static void mostrarMenuPrincipal(const Usuario usuarios[], int usuarioActivo,
                                 const Grupo grupos[], int grupoActivo) {
    printf("\n=============== MENU PRINCIPAL ===============\n");

    if (grupoActivo == -1) {
        printf(" Grupo: Ninguno");
    } else {
        printf(" Grupo: %s", grupos[grupoActivo].nombre);
    }
    if (usuarios[usuarioActivo].esAdministrador) {
        printf("   [Admin]");
    }
    printf("\n");

    printf("----------------------------------------------\n");
    printf("  1. Registrar gasto\n");
    printf("  2. Consultar saldos\n");
    printf("  3. Simplificar deudas\n");
    printf("  4. Registrar liquidacion (pago)\n");
    printf("  5. Reportes\n");
    printf("  6. Cambiar de grupo\n");
    printf("  7. Administracion (grupos/miembros/categorias)\n");
    printf("  0. Guardar y salir\n");
    printf("----------------------------------------------\n");
    printf(" Opcion: ");
}

int main(void) {
    /* Datos del sistema: un arreglo y un contador por estructura */
    Usuario usuarios[MAX_USUARIOS];
    int numUsuarios = 0;
    Grupo grupos[MAX_GRUPOS];
    int numGrupos = 0;
    MiembroGrupo miembros[MAX_MEMBRESIAS];
    int numMiembros = 0;
    Categoria categorias[MAX_CATEGORIAS];
    int numCategorias = 0;
    Gasto gastos[MAX_GASTOS];
    int numGastos = 0;
    DivisionGasto divisiones[MAX_DIVISIONES];
    int numDivisiones = 0;
    Liquidacion liquidaciones[MAX_LIQUIDACIONES];
    int numLiquidaciones = 0;
    int usuarioActivo = -1; /* -1 significa que no hay usuario logueado */
    int grupoActivo = -1; /* Posicion del grupo activo; -1 si no hay */
    int opcion = 0;       /* Opcion elegida en el menu principal */

    printf("Micha y Micha\n");

    /* Carga de datos al iniciar (RF-17). Si un archivo falta o esta
       danado, se avisa y se continua con datos vacios. */
    if (!cargarUsuarios(usuarios, &numUsuarios)) {
        printf("Aviso: no se encontraron usuarios guardados.\n");
    }
    
    if( !cargarGrupos(grupos, &numGrupos)) {
        printf("Aviso: no se encontraron grupos guardados.\n");
    }
    if( !cargarMiembros(miembros, &numMiembros)) {
        printf("Aviso: no se encontraron miembros guardados.\n");
    }
    if( !cargarGastos(gastos, &numGastos)) {
        printf("Aviso: no se encontraron gastos guardados.\n");
    }
    if( !cargarDivisiones(divisiones, &numDivisiones)) {
        printf("Aviso: no se encontraron divisiones guardadas.\n");
    }
    if( !cargarLiquidaciones(liquidaciones, &numLiquidaciones)) {
        printf("Aviso: no se encontraron liquidaciones guardadas.\n");
    }

    if (!cargarCategorias(categorias, &numCategorias)) {
        printf("Aviso: se crearon las categorias predeterminadas.\n");
        crearCategoriasPredeterminadas(categorias, &numCategorias);
    }

        /* Si no hay nadie, el primero que se registra es el Administrador (E3) */
    if (numUsuarios == 0) {
        printf("\nNo hay usuarios. Registra al Administrador.\n");
        registrarUsuario(usuarios, &numUsuarios);
    }

    /* Inicio de sesion (RF-02). Si elige 0, sale del programa. */
    usuarioActivo = iniciarSesion(usuarios, numUsuarios);
    if (usuarioActivo == -1) {
        printf("Hasta luego.\n");
        return 0;
    }

    /* Menu principal: se repite hasta elegir 0 */
    do {
        mostrarMenuPrincipal(usuarios, usuarioActivo, grupos, grupoActivo);
        opcion = leerEntero(0, 7);

        switch (opcion) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                printf("Disponible en un proximo incremento.\n");
                break;
            case 0:
                /* Aqui va el guardado (paso 4) */
                break;
        }
    } while (opcion != 0);

    return 0;
}