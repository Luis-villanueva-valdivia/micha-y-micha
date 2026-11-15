/*
 * Archivo:     grupos.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       15/11/2026
 * Version:     0.2
 * Descripcion: Gestion de grupos de roomies: listar, crear, renombrar y
 *              eliminar grupos (RF-03, CU-09), y de sus miembros (RF-04,
 *              CU-10).
 */
#ifndef MICHAYMICHA_GRUPOS_H
#define MICHAYMICHA_GRUPOS_H

#include "estructuras.h"

/* Muestra el numero y nombre de cada grupo para elegirlo */
void listarGrupos(const Grupo grupos[], int numGrupos);

/* Devuelve la posicion del grupo con ese id, o -1 si no existe */
int buscarGrupoPorId(const Grupo grupos[], int numGrupos, int idGrupo);

/* Pide el nombre de un grupo nuevo y lo agrega con idAdministrador como
   administrador. Devuelve 1 si lo creo, 0 si no (lleno o repetido). */
int crearGrupo(Grupo grupos[], int *numGrupos, int idAdministrador);

/* Pide elegir un grupo y su nombre nuevo. Devuelve 1 si lo renombro,
   0 si no. */
int renombrarGrupo(Grupo grupos[], int numGrupos);

/* Pide elegir un grupo y lo elimina junto con sus membresias. Devuelve
   el id del grupo eliminado, o 0 si no se elimino. */
int eliminarGrupo(Grupo grupos[], int *numGrupos,
                  MiembroGrupo miembros[], int *numMiembros);

/* Devuelve 1 si el usuario pertenece al grupo, 0 si no */
int esMiembro(const MiembroGrupo miembros[], int numMiembros, int idGrupo,
              int idUsuario);

/* Devuelve cuantos miembros tiene el grupo */
int contarMiembros(const MiembroGrupo miembros[], int numMiembros,
                   int idGrupo);

/* Muestra con un numero el nombre de cada miembro del grupo */
void listarMiembros(const MiembroGrupo miembros[], int numMiembros,
                    int idGrupo, const Usuario usuarios[], int numUsuarios);

/* Agrega al grupo un usuario existente o uno nuevo. Devuelve 1 si lo
   agrego, 0 si no. */
int agregarMiembro(MiembroGrupo miembros[], int *numMiembros, int idGrupo,
                   Usuario usuarios[], int *numUsuarios);

/* Pide elegir un miembro del grupo y lo quita. Devuelve 1 si lo quito,
   0 si no. */
int quitarMiembro(MiembroGrupo miembros[], int *numMiembros, int idGrupo,
                  const Usuario usuarios[], int numUsuarios);

#endif /* MICHAYMICHA_GRUPOS_H */
