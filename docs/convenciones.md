# Convenciones del proyecto — Micha y Micha

Reglas con las que se trabaja el proyecto. El estándar de codificación es el de la **sección 3 de la propuesta** ([docs/propuesta/VillanuevaLuis_Propuesta.pdf](propuesta/VillanuevaLuis_Propuesta.pdf)); aquí se resume y se agregan las reglas de Git y GitHub.

---

## 1. Entorno y versiones

| Componente | Versión / estándar |
|---|---|
| Lenguaje | C99 (`-std=c99`) |
| Compilador | GCC (MinGW-w64 en Windows) |
| Banderas | `-Wall -Wextra`: el código debe compilar **sin advertencias** |
| Bibliotecas | Solo estándar: `stdio.h`, `stdlib.h`, `string.h`, `ctype.h`. Sin `conio.h` (RNF-01) |
| Editor y depuración | Visual Studio Code y GDB |

**Cómo verificarlo:** `gcc --version` en la terminal.

---

## 2. Milestones, issues y tablero

- Cada **incremento** de la propuesta (§4.1) es un **milestone** en GitHub con su fecha límite.
- Cada tarea es un **issue** `ISS-XX`, ligado a sus requerimientos (RF/RNF), con milestone y labels. La lista completa está en [docs/planeacion/planeacion.md](planeacion/planeacion.md).
- El **tablero** de GitHub Projects tiene las columnas *Pendiente*, *En progreso* y *Hecho*.
- Al cerrar cada incremento se crea su **etiqueta**: `v0.1`, `v0.2`, `v0.3`, `v0.4`, `v1.0`.

---

## 3. Ramas

```
main   ← siempre compila y funciona
  └── tipo/iss-XX-descripcion   ← una rama por issue (recomendado)
```

- Formato de rama: `tipo/iss-XX-descripcion`, con `XX` a dos dígitos, en minúsculas, sin acentos y con guiones.
- Al terminar el issue se fusiona a `main` y se borra la rama.
- Nunca se sube a `main` código que no compila.

| Tipo | Uso | Ejemplo |
|---|---|---|
| `feature` | Funcionalidad nueva | `feature/iss-06-inicio-sesion` |
| `fix` | Corrección de un error | `fix/iss-15-residuo-division` |
| `docs` | Documentación | `docs/iss-27-manual-usuario` |
| `test` | Casos de prueba | `test/iss-26-pruebas-completas` |
| `chore` | Estructura, Makefile, `.gitignore` | `chore/iss-01-estructura` |

```bash
git switch main
git pull
git switch -c feature/iss-06-inicio-sesion
```

---

## 4. Commits

Formato: **`tipo: descripción (iss-XX)`**

- `tipo` en minúsculas, de la lista de abajo.
- Descripción en español, en presente e imperativo, sin punto final, de 72 caracteres o menos.
- Termina con el issue entre paréntesis. En el commit que termina el issue se agrega `Closes #XX` en una línea aparte para que GitHub lo cierre solo.

| Tipo | Uso |
|---|---|
| `feat` | Funcionalidad nueva |
| `fix` | Corrección de un error |
| `docs` | Solo documentación |
| `style` | Formato del código sin cambiar su comportamiento |
| `refactor` | Cambio interno sin cambiar el comportamiento |
| `test` | Pruebas |
| `chore` | Configuración, estructura de carpetas, `Makefile`, `.gitignore` |

Ejemplos:

```
chore: agrega la estructura de carpetas y el Makefile (iss-01)
feat: agrega la division personalizada de gastos (iss-16)
fix: asigna el residuo de la division al pagador (iss-15)
```

Commits **pequeños y seguidos**: uno por cada avance que ya funcione.

---

## 5. Estándar de codificación (resumen de la propuesta, §3)

### 5.1 Nombrado

| Elemento | Convención | Ejemplos |
|---|---|---|
| Variables | `camelCase`, en español y descriptivas | `montoCentavos`, `numGastos`, `idPagador` |
| Contadores de ciclo | Una letra solo en ciclos cortos | `i`, `j` |
| Funciones | `camelCase`, empiezan con verbo en infinitivo | `registrarGasto()`, `calcularSaldos()` |
| Estructuras (`typedef struct`) | `PascalCase`, sustantivo en singular | `Usuario`, `Gasto`, `DivisionGasto` |
| Macros y constantes | `MAYUSCULAS_CON_GUION_BAJO` | `MAX_MIEMBROS`, `ARCHIVO_GASTOS` |
| Enumeraciones | Tipo en `PascalCase`, valores en mayúsculas | `TipoDivision { DIVISION_IGUAL, DIVISION_PERSONALIZADA }` |
| Apuntadores | `*` junto al nombre; prefijo `p` solo si aclara | `Gasto *gastos`, `int *pNumGastos` |
| Archivos | Minúsculas, un módulo por par `.c`/`.h` | `gastos.c`, `gastos.h` |
| Guardas de encabezado | `MICHAYMICHA_MODULO_H` | `#ifndef MICHAYMICHA_GASTOS_H` |

### 5.2 Módulos

| Módulo | Responsabilidad |
|---|---|
| `main.c` | Punto de entrada y menú principal |
| `estructuras.h` | `typedef struct` y macros globales (`MAX_*`) |
| `usuarios.c/.h` | Alta de usuarios e inicio de sesión |
| `grupos.c/.h` | Grupos y miembros |
| `gastos.c/.h` | Registro, división y eliminación de gastos |
| `saldos.c/.h` | Cálculo de saldos y simplificación de deudas |
| `reportes.c/.h` | Historial y reportes |
| `archivos.c/.h` | Guardar y cargar datos |
| `utilidades.c/.h` | Lectura validada de entradas, fechas y formato de montos |

- Los `.c` van en `src/` y los `.h` en `include/`. Cada `.h` contiene solo prototipos, macros y tipos.
- **Sin variables globales**: los datos se pasan por apuntador a las funciones.
- Los montos se guardan en **centavos como `long`** (RNF-04).

### 5.3 Formato

- Sangría de 4 espacios (sin tabuladores) y líneas de máximo 100 caracteres.
- Llaves estilo K&R: la de apertura en la misma línea; siempre con llaves, incluso en `if` de una línea.
- Un espacio alrededor de operadores y después de comas; una línea en blanco entre funciones.
- Una declaración por línea, inicializada al declararse.
- Funciones cortas (idealmente menos de 40 líneas) con una sola responsabilidad.

### 5.4 Comentarios

Encabezado de archivo, al inicio de cada `.c` y `.h`:

```c
/*
 * Archivo:     saldos.c
 * Proyecto:    Micha y Micha
 * Autor:       Luis Adrian Villanueva Valdivia
 * Fecha:       28/10/2026
 * Version:     1.0
 * Descripcion: Calculo de saldos por miembro y simplificacion
 *              de deudas mediante un algoritmo greedy.
 */
```

Bloque de función, antes de cada función en el `.c`:

```c
/*
 * Funcion:     simplificarDeudas
 * Descripcion: Genera la lista minima de transferencias emparejando
 *              al mayor deudor con el mayor acreedor.
 * Parametros:  saldos         - arreglo de saldos en centavos (entrada)
 *              numMiembros    - cantidad de elementos del arreglo
 *              transferencias - arreglo donde se escriben los resultados
 * Retorno:     Numero de transferencias generadas (maximo numMiembros - 1).
 * Precondic.:  La suma de los saldos es cero.
 */
```

- Comentarios en línea solo para explicar el **porqué** de una decisión no evidente.
- Cada `struct` lleva un comentario breve por campo.
- Se elimina el código comentado o de prueba antes de cada entrega.

---

## 6. Estructura del proyecto

| Carpeta | Qué va ahí |
|---|---|
| `src/` | Archivos `.c` |
| `include/` | Archivos `.h` |
| `datos/` | `usuarios.txt`, `grupos.txt`, `gastos.txt`, … que genera el programa (ignorados por Git) |
| `docs/propuesta/` | Propuesta del proyecto (PDF) |
| `docs/planeacion/` | Milestones e issues |
| `docs/diagramas/` | Diagramas exportados |
| `docs/manuales/` | Manual de usuario |
| `tests/` | Casos de prueba por caso de uso: entrada y salida esperada |

---

## 7. Otras reglas

- **`.gitkeep`:** al agregar el primer archivo real a una carpeta, se borra su `.gitkeep` en el mismo commit.
- **El repositorio es público.** Nunca se suben datos personales reales en `datos/` ni en `tests/`.
- **Antes de cada commit:** `make` compila sin advertencias y el programa corre.
