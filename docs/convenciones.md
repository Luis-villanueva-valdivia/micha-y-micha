# Convenciones del proyecto — Micha y Micha

Reglas con las que se trabaja el proyecto. Siguen la misma idea que las de Nexus FMAT, adaptadas a un proyecto individual en C.

---

## 1. Entorno y versiones

| Componente | Versión / estándar |
|---|---|
| Lenguaje | C11 (`-std=c11`) |
| Compilador | GCC (MinGW-w64 en Windows) |
| Banderas | `-Wall -Wextra`: el código debe compilar **sin advertencias** |

**Cómo verificarlo:** `gcc --version` en la terminal.

---

## 2. Issues y ramas

Cada parte del trabajo es un **issue** en GitHub (`ISS-01`, `ISS-02`, …), y así queda el registro de qué se hizo y cuándo.

```
main   ← siempre compila y funciona
  └── tipo/iss-XX-descripcion   ← una rama por issue (opcional pero recomendado)
```

- Formato de rama: `tipo/iss-XX-descripcion`, con `XX` a dos dígitos, en minúsculas, sin acentos y con guiones.
- Al terminar el issue se fusiona a `main` y se borra la rama.
- Nunca se sube a `main` código que no compila.

| Tipo | Uso | Ejemplo |
|---|---|---|
| `feature` | Funcionalidad nueva | `feature/iss-03-registro-roomies` |
| `fix` | Corrección de un error | `fix/iss-08-division-redondeo` |
| `docs` | Documentación | `docs/iss-01-propuesta` |
| `test` | Casos de prueba | `test/iss-10-pruebas-gastos` |
| `chore` | Estructura, Makefile, `.gitignore` | `chore/iss-02-estructura` |

```bash
git switch main
git pull
git switch -c feature/iss-03-registro-roomies
```

---

## 3. Commits

Formato: **`tipo: descripción (iss-XX)`**

- `tipo` en minúsculas, de la lista de abajo.
- Descripción en español, en presente e imperativo, sin punto final, de 72 caracteres o menos.
- Termina con el issue entre paréntesis.

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
chore: agrega la estructura de carpetas y el Makefile (iss-02)
docs: agrega la propuesta del proyecto (iss-01)
feat: registra roomies en un arreglo de estructuras (iss-03)
fix: evita dividir entre cero si no hay roomies (iss-08)
```

Commits **pequeños y seguidos**: uno por cada cosa que ya funcione.

---

## 4. Nombres

| Elemento | Convención | Ejemplo |
|---|---|---|
| Archivos `.c` y `.h` | `snake_case`, el `.h` con el mismo nombre que su `.c` | `gastos.c` / `gastos.h` |
| Funciones | `snake_case`, empiezan con verbo | `registrar_gasto()`, `calcular_deudas()` |
| Variables | `snake_case`, descriptivas | `total_gastos`, `num_roomies` |
| Constantes y macros | `MAYUSCULAS_CON_GUION_BAJO` | `MAX_ROOMIES`, `MAX_NOMBRE` |
| Estructuras (`typedef`) | `PascalCase`, singular | `Roomie`, `Gasto` |

Los identificadores van en español y sin acentos ni ñ (`anio`, `companero`).

---

## 5. Estándares de código

### 5.1 Generales

- **Indentación de 4 espacios**, sin tabuladores. UTF-8 y salto de línea al final del archivo.
- **Sin números mágicos.** Todo valor con significado va en una constante: `#define MAX_ROOMIES 10`.
- **Funciones pequeñas con una sola responsabilidad.** Si pasa de unas 30 líneas, probablemente hace demasiado.
- **`main.c` solo tiene el menú**; la lógica vive en los módulos.
- **No repetir código:** si algo se usa en dos lugares, va en una función.
- **No dejar código comentado** ni `printf` de depuración en lo que se sube a `main`.

### 5.2 Módulos y archivos de encabezado

- Cada módulo tiene su `.c` en `src/` y su `.h` en `include/`.
- El `.h` lleva guardas de inclusión y solo contiene estructuras, constantes y prototipos:

```c
#ifndef GASTOS_H
#define GASTOS_H

/* ... */

#endif
```

### 5.3 Comentarios y documentación

- **Todo archivo** empieza con un bloque que dice qué hace.
- **Toda función** lleva un comentario con qué hace, sus parámetros y qué regresa:

```c
/*
 * Suma el monto de todos los gastos registrados.
 *
 * gastos:     arreglo de gastos.
 * num_gastos: cuántos gastos hay en el arreglo.
 * Regresa:    el total en pesos.
 */
```

- Dentro del código se comenta el **porqué**, no el qué. Los comentarios van en español.

### 5.4 Entrada y apuntadores

- Validar **toda** entrada del usuario (opciones fuera de rango, montos negativos, cadenas demasiado largas).
- Leer cadenas con `fgets` (nunca `gets`) y respetar el tamaño del arreglo.
- Comprobar que los apuntadores no sean `NULL` antes de usarlos, y que `fopen` haya funcionado antes de leer o escribir un archivo.

---

## 6. Estructura del proyecto

| Carpeta | Qué va ahí |
|---|---|
| `src/` | Archivos `.c`: `main.c` y un archivo por módulo |
| `include/` | Archivos `.h` de cada módulo |
| `data/` | Archivos que el programa guarda y lee al usarse (ignorados por Git) |
| `docs/propuesta/` | Propuesta del proyecto y requerimientos |
| `docs/diagramas/` | Diagrama de casos de uso y otros diagramas |
| `docs/manuales/` | Manual de usuario y manual técnico |
| `tests/` | Casos de prueba: entrada y salida esperada |

---

## 7. Otras reglas

- **`.gitkeep`:** al agregar el primer archivo real a una carpeta, se borra su `.gitkeep` en el mismo commit.
- **El repositorio es público.** Nunca se suben datos personales reales de roomies en `data/` ni en `tests/`.
- **Antes de cada commit:** `make` compila sin advertencias y el programa corre.
