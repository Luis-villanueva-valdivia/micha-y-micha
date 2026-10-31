/*
 * Archivo:     usuarios.h
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       30/10/2026
 * Version:     0.1
 * Descripcion: Alta de usuarios con nombre y PIN de 4 digitos, listado
 *              sin mostrar el PIN e inicio de sesion (RF-01, RF-02,
 *              RNF-08).
 */
#ifndef MICHAYMICHA_USUARIOS_H
#define MICHAYMICHA_USUARIOS_H

#include "estructuras.h"

/* Muestra el numero y nombre de cada usuario, sin el PIN */
void listarUsuarios(const Usuario usuarios[], int numUsuarios);

/* Pide nombre y PIN y agrega el usuario al arreglo. El primero que se
   registra queda como Administrador. Devuelve 1 si lo agrego, 0 si no. */
int registrarUsuario(Usuario usuarios[], int *numUsuarios);

/* Pide elegir un usuario de la lista y su PIN (3 intentos). Devuelve la
   posicion del usuario en el arreglo, o -1 si no entro. */
int iniciarSesion(const Usuario usuarios[], int numUsuarios);

#endif /* MICHAYMICHA_USUARIOS_H */