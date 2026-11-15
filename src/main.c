/*
 * Archivo:     main.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.3
 * Descripcion: Punto de entrada y menu principal. Cada opcion llama a
 *              una funcion de su modulo; aqui no va logica de negocio.
 */
#include <stdio.h>
#include "estructuras.h"
#include "archivos.h"
#include "categorias.h"
#include "gastos.h"
#include "grupos.h"
#include "saldos.h"
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
    printf("  1. Gastos (registrar / eliminar)\n");
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
 * Funcion:     menuGastos
 * Descripcion: Submenu de la opcion 1: registrar un gasto (RF-06) o
 *              eliminar uno (RF-09). Guarda gastos y divisiones despues de
 *              cada cambio (RF-16). Pide tener un grupo activo.
 * Parametros:  los arreglos y contadores de gastos y divisiones, los
 *              datos del grupo, el usuario activo y el id del grupo
 *              activo.
 * Retorno:     Ninguno.
 */
static void menuGastos(Gasto gastos[], int *numGastos,
                       DivisionGasto divisiones[], int *numDivisiones,
                       const Usuario usuarios[], int numUsuarios,
                       const MiembroGrupo miembros[], int numMiembros,
                       const Categoria categorias[], int numCategorias,
                       int usuarioActivo, int idGrupoActivo) {
    int opcion = 0;
    int cambio = 0;

    if (idGrupoActivo == 0) {
        printf("Primero elige un grupo activo (opcion 6).\n");
        return;
    }

    do {
        printf("\n--- Gastos ---\n");
        printf("1. Registrar gasto\n");
        printf("2. Eliminar gasto\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        opcion = leerEntero(0, 2);

        cambio = 0;
        switch (opcion) {
            case 1:
                cambio = registrarGasto(gastos, numGastos, divisiones,
                                        numDivisiones, idGrupoActivo,
                                        usuarios, numUsuarios, miembros,
                                        numMiembros, categorias,
                                        numCategorias);
                break;
            case 2:
                cambio = eliminarGasto(gastos, numGastos, divisiones,
                                       numDivisiones, idGrupoActivo,
                                       &usuarios[usuarioActivo], usuarios,
                                       numUsuarios);
                break;
        }
        /* Se guarda al registrar cada cambio (RF-16) */
        if (cambio && (!guardarGastos(gastos, *numGastos) ||
                       !guardarDivisiones(divisiones, *numDivisiones))) {
            printf("Error: no se pudieron guardar los gastos.\n");
        }
    } while (opcion != 0);
}

/*
 * Funcion:     menuGrupos
 * Descripcion: Submenu para crear, renombrar y eliminar grupos (RF-03).
 *              Al crear un grupo, el Administrador queda como miembro
 *              y, si no habia grupo activo, el nuevo pasa a ser el activo.
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
                    /* Si no habia grupo activo, el nuevo queda como activo */
                    if (*idGrupoActivo == 0) {
                        *idGrupoActivo = grupos[*numGrupos - 1].id;
                    }
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
 * Funcion:     menuCategorias
 * Descripcion: Submenu para agregar, renombrar y eliminar categorias
 *              (RF-05).
 * Parametros:  categorias    - arreglo de categorias
 *              numCategorias - apuntador al contador de categorias
 *              gastos        - arreglo de gastos (para no borrar usadas)
 *              numGastos     - cuantos gastos hay
 * Retorno:     Ninguno.
 */
static void menuCategorias(Categoria categorias[], int *numCategorias,
                           const Gasto gastos[], int numGastos) {
    int opcion = 0;

    do {
        printf("\n--- Categorias ---\n");
        listarCategorias(categorias, *numCategorias);
        printf("1. Agregar categoria\n");
        printf("2. Renombrar categoria\n");
        printf("3. Eliminar categoria\n");
        printf("0. Regresar\n");
        printf("Opcion: ");
        opcion = leerEntero(0, 3);

        switch (opcion) {
            case 1:
                agregarCategoria(categorias, numCategorias);
                break;
            case 2:
                renombrarCategoria(categorias, *numCategorias);
                break;
            case 3:
                eliminarCategoria(categorias, numCategorias, gastos, numGastos);
                break;
        }
    } while (opcion != 0);
}

/*
 * Funcion:     cambiarGrupoActivo
 * Descripcion: Muestra los grupos a los que pertenece el usuario (el
 *              Administrador ve todos) y pide elegir el grupo activo.
 * Parametros:  grupos      - arreglo de grupos
 *              numGrupos   - cuantos grupos hay
 *              miembros    - arreglo de membresias
 *              numMiembros - cuantas membresias hay
 *              usuario     - usuario que inicio sesion
 * Retorno:     El id del grupo elegido, o 0 si no eligio ninguno.
 */
static int cambiarGrupoActivo(const Grupo grupos[], int numGrupos,
                              const MiembroGrupo miembros[], int numMiembros,
                              const Usuario *usuario) {
    int posiciones[MAX_GRUPOS]; /* Posicion de cada grupo que se muestra */
    int cuantos = 0;
    int opcion = 0;
    int i = 0;

    printf("\n--- Cambiar de grupo ---\n");
    for (i = 0; i < numGrupos; i++) {
        if (usuario->esAdministrador ||
            esMiembro(miembros, numMiembros, grupos[i].id, usuario->id)) {
            posiciones[cuantos] = i;
            cuantos++;
            printf("%d. %s\n", cuantos, grupos[i].nombre);
        }
    }
    if (cuantos == 0) {
        printf("No perteneces a ningun grupo.\n");
        return 0;
    }
    printf("0. Cancelar\n");
    printf("Elige el grupo: ");
    opcion = leerEntero(0, cuantos);
    if (opcion == 0) {
        return 0;
    }
    return grupos[posiciones[opcion - 1]].id;
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
                               const Gasto gastos[], int numGastos,
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
        printf("  3. Categorias\n");
        printf("  0. Regresar\n");
        printf(" Opcion: ");
        opcion = leerEntero(0, 3);

        switch (opcion) {
            case 1:
                menuGrupos(grupos, numGrupos, miembros, numMiembros,
                           usuarios[usuarioActivo].id, idGrupoActivo);
                break;
            case 2:
                menuMiembros(miembros, numMiembros, usuarios, numUsuarios,
                             *idGrupoActivo);
                break;
            case 3:
                menuCategorias(categorias, numCategorias, gastos, numGastos);
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
    int idElegido = 0;    /* Grupo elegido en la opcion 6 */
    int gruposConSaldo[MAX_GRUPOS]; /* Grupos que no se pueden eliminar */
    int idsConSaldo[MAX_MIEMBROS];  /* Miembros que no se pueden quitar */
    int numBloqueados = 0;
    int i = 0;

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

    /* Grupo activo inicial: el primero al que pertenece el usuario */
    for (i = 0; i < numGrupos && idGrupoActivo == 0; i++) {
        if (esMiembro(miembros, numMiembros, grupos[i].id,
                      usuarios[usuarioActivo].id)) {
            idGrupoActivo = grupos[i].id;
        }
    }

    /* Menu principal: se repite hasta elegir 0 */
    do {
        mostrarMenuPrincipal(usuarios, usuarioActivo, grupos,
                             buscarGrupoPorId(grupos, numGrupos, idGrupoActivo));
        opcion = leerEntero(0, 7);

        switch (opcion) {
            case 1:
                menuGastos(gastos, &numGastos, divisiones, &numDivisiones,
                           usuarios, numUsuarios, miembros, numMiembros,
                           categorias, numCategorias, usuarioActivo,
                           idGrupoActivo);
                break;
            case 2:
                if (idGrupoActivo == 0) {
                    printf("Primero elige un grupo activo (opcion 6).\n");
                } else {
                    mostrarSaldos(idGrupoActivo, usuarios, numUsuarios,
                                  miembros, numMiembros, gastos, numGastos,
                                  divisiones, numDivisiones, liquidaciones,
                                  numLiquidaciones);
                    mostrarDeudasSimplificadas(idGrupoActivo, usuarios,
                                               numUsuarios, miembros,
                                               numMiembros, gastos, numGastos,
                                               divisiones, numDivisiones,
                                               liquidaciones,
                                               numLiquidaciones);
                }
                break;
            case 3:
            case 4:
            case 5:
                printf("Disponible en un proximo incremento.\n");
                break;
            case 6:
                idElegido = cambiarGrupoActivo(grupos, numGrupos, miembros,
                                               numMiembros,
                                               &usuarios[usuarioActivo]);
                if (idElegido != 0) {
                    idGrupoActivo = idElegido;
                }
                break;
            case 7:
                /* Grupos y miembros con saldo pendiente no se pueden
                   eliminar ni quitar (E2 de CU-09 y CU-10) */
                numBloqueados = 0;
                for (i = 0; i < numGrupos; i++) {
                    if (usuariosConSaldo(grupos[i].id, miembros, numMiembros,
                                         gastos, numGastos, divisiones,
                                         numDivisiones, liquidaciones,
                                         numLiquidaciones, idsConSaldo) > 0) {
                        gruposConSaldo[numBloqueados] = grupos[i].id;
                        numBloqueados++;
                    }
                }
                fijarBloqueosSaldo(gruposConSaldo, numBloqueados, idGrupoActivo,
                                   idsConSaldo,
                                   usuariosConSaldo(idGrupoActivo, miembros,
                                                    numMiembros, gastos,
                                                    numGastos, divisiones,
                                                    numDivisiones,
                                                    liquidaciones,
                                                    numLiquidaciones,
                                                    idsConSaldo));
                menuAdministracion(usuarios, &numUsuarios, grupos, &numGrupos,
                                   miembros, &numMiembros, categorias,
                                   &numCategorias, gastos, numGastos,
                                   usuarioActivo, &idGrupoActivo);
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
