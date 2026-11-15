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
#include "grupos.h"
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

/*
 * Funcion:     menuGrupos
 * Descripcion: Submenu para crear, renombrar y eliminar grupos (RF-03).
 *              Al crear un grupo, el Administrador queda como miembro.
 *              Si se elimina el grupo activo, ya no queda grupo activo.
 * Parametros:  grupos        - arreglo de grupos
 *              numGrupos     - apuntador al contador de grupos
 *              miembros      - arreglo de membresias
 *              numMiembros   - apuntador al contador de membresias
 *              idUsuario     - id del Administrador que usa el menu
 *              idGrupoActivo - apuntador al id del grupo activo (0 = ninguno)
 * Retorno:     Ninguno.
 */
static void menuGrupos(Grupo grupos[], int *numGrupos,
                       MiembroGrupo miembros[], int *numMiembros,
                       int idUsuario, int *idGrupoActivo) {
    int opcion = 0;
    int idEliminado = 0;

    do {
        printf("\n--- Grupos ---\n");
        listarGrupos(grupos, *numGrupos);
        printf("1. Crear grupo\n");
        printf("2. Renombrar grupo\n");
        printf("3. Eliminar grupo\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        opcion = leerEntero(0, 3);

        switch (opcion) {
            case 1:
                if (crearGrupo(grupos, numGrupos, idUsuario) &&
                    *numMiembros < MAX_MEMBRESIAS) {
                    /* El creador queda como miembro del grupo nuevo */
                    miembros[*numMiembros].idGrupo = grupos[*numGrupos - 1].id;
                    miembros[*numMiembros].idUsuario = idUsuario;
                    (*numMiembros)++;
                }
                break;
            case 2:
                renombrarGrupo(grupos, *numGrupos);
                break;
            case 3:
                idEliminado = eliminarGrupo(grupos, numGrupos, miembros,
                                            numMiembros);
                if (idEliminado != 0 && idEliminado == *idGrupoActivo) {
                    *idGrupoActivo = 0;
                }
                break;
        }
    } while (opcion != 0);
}

/*
 * Funcion:     menuMiembros
 * Descripcion: Submenu para ver, agregar y quitar miembros del grupo
 *              activo (RF-04). Pide tener un grupo activo.
 * Parametros:  miembros      - arreglo de membresias
 *              numMiembros   - apuntador al contador de membresias
 *              usuarios      - arreglo de usuarios
 *              numUsuarios   - apuntador al contador de usuarios
 *              idGrupoActivo - id del grupo activo (0 = ninguno)
 * Retorno:     Ninguno.
 */
static void menuMiembros(MiembroGrupo miembros[], int *numMiembros,
                         Usuario usuarios[], int *numUsuarios,
                         int idGrupoActivo) {
    int opcion = 0;

    if (idGrupoActivo == 0) {
        printf("Primero elige un grupo activo (opcion 6).\n");
        return;
    }

    do {
        printf("\n--- Miembros del grupo ---\n");
        listarMiembros(miembros, *numMiembros, idGrupoActivo, usuarios,
                       *numUsuarios);
        printf("1. Agregar miembro\n");
        printf("2. Quitar miembro\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        opcion = leerEntero(0, 2);

        switch (opcion) {
            case 1:
                agregarMiembro(miembros, numMiembros, idGrupoActivo, usuarios,
                               numUsuarios);
                break;
            case 2:
                quitarMiembro(miembros, numMiembros, idGrupoActivo, usuarios,
                              *numUsuarios);
                break;
        }
    } while (opcion != 0);
}

/*
 * Funcion:     menuAdministracion
 * Descripcion: Menu de administracion (opcion 7). Solo entra el
 *              Administrador (RNF-08). Al salir guarda los cambios.
 * Parametros:  los arreglos y contadores del sistema, el usuario activo
 *              y el apuntador al id del grupo activo.
 * Retorno:     Ninguno.
 */
static void menuAdministracion(Usuario usuarios[], int *numUsuarios,
                               Grupo grupos[], int *numGrupos,
                               MiembroGrupo miembros[], int *numMiembros,
                               Categoria categorias[], int *numCategorias,
                               int usuarioActivo, int *idGrupoActivo) {
    int opcion = 0;

    if (!usuarios[usuarioActivo].esAdministrador) {
        printf("Solo el Administrador puede entrar a este menu.\n");
        return;
    }

    do {
        printf("\n=========== ADMINISTRACION ===========\n");
        printf("  1. Grupos\n");
        printf("  2. Miembros del grupo activo\n");
        printf("  0. Regresar\n");
        printf(" Opcion: ");
        opcion = leerEntero(0, 2);

        switch (opcion) {
            case 1:
                menuGrupos(grupos, numGrupos, miembros, numMiembros,
                           usuarios[usuarioActivo].id, idGrupoActivo);
                break;
            case 2:
                menuMiembros(miembros, numMiembros, usuarios, numUsuarios,
                             *idGrupoActivo);
                break;
        }
    } while (opcion != 0);

    /* Guarda lo que se haya cambiado (RF-16) */
    if (!guardarUsuarios(usuarios, *numUsuarios) ||
        !guardarGrupos(grupos, *numGrupos) ||
        !guardarMiembros(miembros, *numMiembros) ||
        !guardarCategorias(categorias, *numCategorias)) {
        printf("Error: no se pudieron guardar los cambios.\n");
    }
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
    int idGrupoActivo = 0; /* id del grupo activo; 0 si no hay */
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
        guardarUsuarios(usuarios, numUsuarios);
        printf("Hasta luego.\n");
        return 0;
    }

    /* Menu principal: se repite hasta elegir 0 */
    do {
        mostrarMenuPrincipal(usuarios, usuarioActivo, grupos,
                             buscarGrupoPorId(grupos, numGrupos, idGrupoActivo));
        opcion = leerEntero(0, 7);

        switch (opcion) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                printf("Disponible en un proximo incremento.\n");
                break;
            case 7:
                menuAdministracion(usuarios, &numUsuarios, grupos, &numGrupos,
                                   miembros, &numMiembros, categorias,
                                   &numCategorias, usuarioActivo, &idGrupoActivo);
                break;
            case 0:
                                /* Guardado de datos al salir (RF-16) */
                if (!guardarUsuarios(usuarios, numUsuarios)) {
                    printf("Error: no se pudieron guardar los usuarios.\n");
                }
                if (!guardarGrupos(grupos, numGrupos)) {
                    printf("Error: no se pudieron guardar los grupos.\n");
                }
                if (!guardarMiembros(miembros, numMiembros)) {
                    printf("Error: no se pudieron guardar los miembros.\n");
                }
                if (!guardarCategorias(categorias, numCategorias)) {
                    printf("Error: no se pudieron guardar las categorias.\n");
                }
                if (!guardarGastos(gastos, numGastos)) {
                    printf("Error: no se pudieron guardar los gastos.\n");
                }
                if (!guardarDivisiones(divisiones, numDivisiones)) {
                    printf("Error: no se pudieron guardar las divisiones.\n");
                }
                if (!guardarLiquidaciones(liquidaciones, numLiquidaciones)) {
                    printf("Error: no se pudieron guardar las liquidaciones.\n");
                }
                printf("Datos guardados. Hasta luego.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
