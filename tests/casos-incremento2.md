# Casos de prueba · Incremento 2 (v0.2)

- **Issue:** ISS-13 · Revisar el incremento 2 y etiquetar v0.2
- **Fecha:** 15/11/2026
- **Versión probada:** `main` en `baa250b` (merge del PR #38) más la corrección de esta rama
- **Compilación:** `make clean && make` → 0 advertencias

Cada caso se puede repetir así: se borra `datos/*.txt` cuando el caso lo pide,
se ejecuta `./michaymicha` y se escriben las entradas en orden. Luis (PIN `1234`)
es el Administrador; Ana (PIN `1111`) es Roomie.

## CU-09 · Gestionar grupos (opción 7 → 1)

| ID | Ruta | Estado inicial | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|---|
| P01 | Flujo principal · crear | Solo Luis | `1`, `Depa Centro` | Se crea el grupo y Luis queda como miembro | "Grupo "Depa Centro" creado." · `grupos.txt` = `1\|Depa Centro\|1` · `miembros.txt` = `1\|1` | ✅ |
| P02 | E1 · Nombre repetido al crear | Existe "Depa Centro" | `1`, `Depa Centro` | Rechaza el nombre | "Error: Ya existe un grupo con ese nombre." | ✅ |
| P03 | E1 · Nombre repetido al renombrar | "Depa Centro" y "Casa Playa" | `2`, `2`, `Depa Centro` | Rechaza el nombre | "Error: Ya existe un grupo con ese nombre." | ✅ |
| P04 | Renombrar | Igual que P03 | `2`, `2`, `Casa Norte` | Cambia el nombre | "Grupo renombrado." | ✅ |
| P05 | E3 · Máximo de grupos | 5 grupos | `1` | Avisa que se alcanzó el máximo | "Error: Ya se alcanzo el maximo de 5 grupos." | ✅ |
| P06 | Eliminar · confirmar "no" | 5 grupos | `3`, `5`, `0` | No elimina | "No se elimino el grupo." | ✅ |
| P07 | Eliminar · confirmar "sí" | 5 grupos | `3`, `5`, `1` | Elimina el grupo y sus membresías | "Grupo eliminado." · quedan 4 grupos · sin membresías del grupo borrado | ✅ |
| P08 | Cancelar al elegir | Varios grupos | `3`, `0` | No elimina nada | Regresa al submenú | ✅ |
| P09 | Eliminar el grupo activo | Grupo activo "Depa Centro" | `3`, `1`, `1` | Ya no queda grupo activo | Menú principal: `Grupo: Ninguno   [Admin]` | ✅ |
| P10 | Grupo activo al crear el primero | Luis sin grupos | `1`, `Depa Centro`, salir al menú | El grupo nuevo queda activo | Antes: `Grupo: Ninguno`. **Corregido en esta rama:** `Grupo: Depa Centro` | ✅ (tras fix) |
| — | E2 · Grupo con saldos pendientes | — | — | No se elimina | Pendiente: depende del cálculo de saldos (ISS-19) | ⏳ |

## CU-10 · Gestionar miembros (opción 7 → 2)

| ID | Ruta | Estado inicial | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|---|
| P11 | Sin grupo activo | Grupo activo: Ninguno | `2` | Pide elegir un grupo antes | "Primero elige un grupo activo (opcion 6)." | ✅ |
| P12 | E1 · Ya es miembro | Luis en "Depa Centro" | `1`, `1`, `1` (Luis) | Avisa y no lo duplica | "Error: Luis ya es miembro del grupo." | ✅ |
| P13 | Agregar usuario nuevo | — | `1`, `2`, `Ana`, `1111` | Registra a Ana y la agrega | "Usuario registrado." · "Ana se agrego al grupo." · Ana queda como Roomie | ✅ |
| P14 | Quitar miembro | Luis, Ana, Beto | `2`, `3` | Quita a Beto sin tocar otros grupos | "Miembro quitado del grupo." · las membresías de otros grupos siguen igual | ✅ |
| P15 | E3 · Máximo de miembros | Grupo con 10 miembros | `1` | Avisa y no pide datos | "Error: El grupo ya tiene 10 miembros." | ✅ |
| — | E2 · Miembro con saldo distinto de cero | — | — | No se quita | Pendiente: depende del cálculo de saldos (ISS-19) | ⏳ |

## CU-11 · Gestionar categorías (opción 7 → 3)

| ID | Ruta | Estado inicial | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|---|
| P16 | Agregar | 5 predeterminadas | `1`, `Internet` | Se agrega con id 6 | "Categoria "Internet" agregada." | ✅ |
| P17 | E1 · Nombre repetido al agregar | Igual | `1`, `Renta` | Rechaza el nombre | "Error: Ya existe una categoria con ese nombre." | ✅ |
| P18 | E1 · Nombre repetido al renombrar | Igual | `2`, `6`, `Super` | Rechaza el nombre | "Error: Ya existe una categoria con ese nombre." | ✅ |
| P19 | Renombrar | Igual | `2`, `6`, `Wifi` | Cambia el nombre | "Categoria renombrada." | ✅ |
| P20 | Eliminar sin gastos | Igual | `3`, `5` (Otros) | La elimina | "Categoria eliminada." | ✅ |
| P21 | E2 · Categoría con gastos | `gastos.txt` con un gasto de categoría 1 | `3`, `1` (Renta) | No la elimina | "Error: La categoria tiene gastos asociados; no se puede eliminar." | ✅ |

## Permisos y grupo activo (ISS-12)

| ID | Caso | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| P22 | Roomie entra a administración | Ana: `7` | Se le niega | "Solo el Administrador puede entrar a este menu." | ✅ |
| P23 | Grupo activo al iniciar sesión | Ana (solo en "Casa Norte") | Entra con su grupo | `Grupo: Casa Norte` | ✅ |
| P24 | Opción 6 como Roomie | Ana: `6` | Solo ve sus grupos | Lista solo `1. Casa Norte` | ✅ |
| P25 | Opción 6 como Administrador | Luis: `6` | Ve todos los grupos | `1. Depa Centro`, `2. Casa Norte` | ✅ |
| P26 | Persistencia | Salir con `0` y volver a entrar | Grupos, miembros y categorías siguen | Se cargan igual desde `datos/` | ✅ |

## Hallazgos

1. **Grupo activo al crear el primer grupo (P10).** Después de crear un grupo, el menú seguía mostrando `Grupo: Ninguno` hasta usar la opción 6 o reiniciar. Se corrigió en esta rama: si no hay grupo activo, el grupo recién creado pasa a ser el activo.
2. **E2 de CU-09 y CU-10.** No eliminar un grupo con saldos ni quitar a un miembro con saldo distinto de cero se completa cuando exista el cálculo de saldos (ISS-19).
3. **Pendiente del incremento 1.** El hallazgo de CU-12 E1 (no permite reintentar si falla el guardado) sigue abierto.
4. **EOF en las lecturas.** Igual que en el incremento 1: si la entrada se termina antes de tiempo, el programa se queda pidiendo datos. No afecta el uso normal en consola.

## Resultado

26 de 26 casos ejecutados pasan (P10 tras la corrección). Quedan 2 rutas alternativas (E2 de CU-09 y CU-10) pendientes para el incremento 4.
