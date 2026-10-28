# Planeación del proyecto — Micha y Micha

Programa de consola en C para que un grupo de roomies registre y divida sus gastos compartidos, consulte saldos y salde deudas con el menor número de transferencias. Esta planeación pasa a GitHub los incrementos de la sección 4 de la [propuesta](../propuesta/VillanuevaLuis_Propuesta.pdf).

**Autor:** Luis Adrián Villanueva Valdivia (@Luis-villanueva-valdivia)
**Materia:** Programación Estructurada · Prof. Emilio Gabriel Rejón Herrera
**Entrega final:** mié 11/11/2026

---

## 1. Supuestos

1. **Modelo incremental.** Cada incremento de la propuesta (§4.1) es un milestone y termina con una versión que compila sin advertencias, una revisión y una etiqueta (`v0.1` … `v1.0`).
2. **IDs de issues.** Los issues se crean en orden (ISS-01 … ISS-28) antes de abrir cualquier PR. Como el repositorio no tiene issues ni PR previos, ISS-NN = #NN.
3. **Requerimientos.** Cada issue indica los RF/RNF que cubre, con la numeración de la propuesta (§2).
4. **Responsable.** Todos los issues son de @Luis-villanueva-valdivia.
5. **Plan de recorte.** Si al 09/11 algo va atrasado, se quita en este orden: (1) el reporte por persona (ISS-25); (2) el filtro por mes de los reportes; (3) eliminar gasto (ISS-17). Nunca se recortan el registro de gastos, la división, los saldos, la simplificación de deudas ni la persistencia, porque son el núcleo del proyecto.

---

## 2. Milestones

| Milestone | Fecha límite | Contenido | Requerimientos | Etiqueta |
|---|---|---|---|---|
| Incremento 1 — Base | vie 30/10/2026 | Estructuras, utilidades, archivos, usuarios e inicio de sesión | RF-01, 02, 16, 17 | `v0.1` |
| Incremento 2 — Grupos | lun 02/11/2026 | Grupos, miembros, categorías y menú de administración | RF-03, 04, 05 | `v0.2` |
| Incremento 3 — Gastos | jue 05/11/2026 | Registro, división igual y personalizada, eliminación | RF-06 a RF-09 | `v0.3` |
| Incremento 4 — Saldos | lun 09/11/2026 | Saldos, simplificación de deudas y liquidaciones | RF-10, 11, 12 | `v0.4` |
| Entrega final | mié 11/11/2026 | Reportes, pruebas completas, manual de usuario | RF-13, 14, 15 | `v1.0` |

En GitHub, cada milestone se crea con el título de la primera columna y una descripción con el contenido.

**Ajuste de fechas (28/10).** Las fechas de la propuesta (§4.1) se recorrieron porque el código empezó el 28/10. La entrega final no cambia.

---

## 3. Labels

| Label | Color sugerido | Uso |
|---|---|---|
| `tipo:feature` | `#1D76DB` | Funcionalidad nueva |
| `tipo:docs` | `#0E8A16` | Documentación |
| `tipo:test` | `#FBCA04` | Pruebas y revisiones de incremento |
| `tipo:chore` | `#BFD4F2` | Estructura, configuración |
| `tipo:fix` | `#D93F0B` | Corrección de errores (se usa al encontrar uno) |
| `prioridad:alta` | `#B60205` | Requerimiento de prioridad Alta en la propuesta |
| `prioridad:media` | `#F9D0C4` | Requerimiento de prioridad Media |

---

## 4. Resumen de issues

| ID | Título | Milestone | Labels | Requerimientos |
|---|---|---|---|---|
| ISS-01 | Crear la estructura del repositorio | Incremento 1 | `tipo:chore` | — |
| ISS-02 | Alinear el repositorio con la propuesta y crear la planeación | Incremento 1 | `tipo:docs` | RNF-09 |
| ISS-03 | Definir estructuras y macros globales | Incremento 1 | `tipo:feature` `prioridad:alta` | RNF-04, RNF-06 |
| ISS-04 | Implementar la lectura validada de entradas | Incremento 1 | `tipo:feature` `prioridad:alta` | RNF-02, RNF-03 |
| ISS-05 | Guardar y cargar los datos en archivos | Incremento 1 | `tipo:feature` `prioridad:alta` | RF-16, RF-17, RNF-07 |
| ISS-06 | Registrar usuarios e iniciar sesión | Incremento 1 | `tipo:feature` `prioridad:alta` | RF-01, RF-02, RNF-08 |
| ISS-07 | Crear el menú principal | Incremento 1 | `tipo:feature` `prioridad:alta` | RNF-02 |
| ISS-08 | Revisar el incremento 1 y etiquetar v0.1 | Incremento 1 | `tipo:test` | — |
| ISS-09 | Gestionar grupos | Incremento 2 | `tipo:feature` `prioridad:alta` | RF-03 |
| ISS-10 | Gestionar miembros | Incremento 2 | `tipo:feature` `prioridad:alta` | RF-04 |
| ISS-11 | Gestionar categorías | Incremento 2 | `tipo:feature` `prioridad:media` | RF-05 |
| ISS-12 | Crear el menú de administración | Incremento 2 | `tipo:feature` `prioridad:alta` | RNF-08 |
| ISS-13 | Revisar el incremento 2 y etiquetar v0.2 | Incremento 2 | `tipo:test` | — |
| ISS-14 | Registrar gasto | Incremento 3 | `tipo:feature` `prioridad:alta` | RF-06 |
| ISS-15 | Dividir gasto en partes iguales | Incremento 3 | `tipo:feature` `prioridad:alta` | RF-07, RNF-04 |
| ISS-16 | Dividir gasto en partes personalizadas | Incremento 3 | `tipo:feature` `prioridad:alta` | RF-08 |
| ISS-17 | Eliminar o corregir gasto | Incremento 3 | `tipo:feature` `prioridad:media` | RF-09 |
| ISS-18 | Revisar el incremento 3 y etiquetar v0.3 | Incremento 3 | `tipo:test` | — |
| ISS-19 | Calcular y consultar saldos | Incremento 4 | `tipo:feature` `prioridad:alta` | RF-10, RNF-04 |
| ISS-20 | Simplificar deudas | Incremento 4 | `tipo:feature` `prioridad:alta` | RF-11 |
| ISS-21 | Registrar liquidación | Incremento 4 | `tipo:feature` `prioridad:alta` | RF-12 |
| ISS-22 | Revisar el incremento 4 y etiquetar v0.4 | Incremento 4 | `tipo:test` | — |
| ISS-23 | Mostrar el historial de gastos | Entrega final | `tipo:feature` `prioridad:media` | RF-13 |
| ISS-24 | Generar el reporte por categoría | Entrega final | `tipo:feature` `prioridad:media` | RF-14 |
| ISS-25 | Generar el reporte por persona | Entrega final | `tipo:feature` `prioridad:media` | RF-15 |
| ISS-26 | Ejecutar los casos de prueba completos | Entrega final | `tipo:test` | RNF-03, RNF-05 |
| ISS-27 | Escribir el manual de usuario | Entrega final | `tipo:docs` | — |
| ISS-28 | Integrar y publicar la versión 1.0 | Entrega final | `tipo:chore` | — |

---

## 5. Issues detallados

Cada bloque se copia tal cual como cuerpo del issue en GitHub.

### Incremento 1 — Base

#### ISS-01 · Crear la estructura del repositorio

- **Labels:** `tipo:chore`

**Descripción.** Carpetas `src/`, `include/`, `datos/`, `docs/` y `tests/`, `Makefile`, `.gitignore` y `README.md`, para que todo el trabajo siguiente tenga dónde ir.

**Criterios de aceptación.**
- [ ] `make` compila sin advertencias y el programa imprime su nombre.
- [ ] Los ejecutables y `datos/` están en `.gitignore`.

#### ISS-02 · Alinear el repositorio con la propuesta y crear la planeación

- **Labels:** `tipo:docs`
- **Requerimientos:** RNF-09

**Descripción.** El repositorio sigue el estándar de la sección 3 de la propuesta (C99, `camelCase`, guardas `MICHAYMICHA_*`, carpeta `datos/`) y documenta cómo se trabaja.

**Criterios de aceptación.**
- [ ] `docs/convenciones.md` resume el estándar de la propuesta y las reglas de Git.
- [ ] La propuesta está en `docs/propuesta/` y esta planeación en `docs/planeacion/`.
- [ ] En GitHub existen los 5 milestones con fecha, los labels de §3 e ISS-01 a ISS-28.
- [ ] Existe el tablero de GitHub Projects con las columnas Pendiente, En progreso y Hecho.

#### ISS-03 · Definir estructuras y macros globales

- **Módulo:** `include/estructuras.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RNF-04, RNF-06

**Descripción.** Los `typedef struct` del modelo de datos de la propuesta (Usuario, Grupo, MiembroGrupo, Categoria, Gasto, DivisionGasto, Liquidacion) y las macros de capacidad.

**Criterios de aceptación.**
- [ ] Están los 7 structs con un comentario por campo.
- [ ] Los montos son `long` en centavos.
- [ ] Las capacidades son macros: 10 miembros por grupo, 5 grupos, 20 categorías y 500 gastos.
- [ ] El `enum TipoDivision` tiene `DIVISION_IGUAL` y `DIVISION_PERSONALIZADA`.

#### ISS-04 · Implementar la lectura validada de entradas

- **Módulo:** `src/utilidades.c`, `include/utilidades.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RNF-02, RNF-03

**Descripción.** Funciones reutilizables para leer enteros en un rango, montos, textos y fechas, y para mostrar montos en pesos.

**Criterios de aceptación.**
- [ ] Una entrada inválida (letras, fuera de rango, fecha inexistente) muestra un mensaje y vuelve a pedir el dato sin cerrar el programa.
- [ ] Los textos se leen con `fgets` sin desbordar el arreglo.
- [ ] Un monto como `840.50` se convierte a `84050` centavos y se muestra como `$840.50`.

#### ISS-05 · Guardar y cargar los datos en archivos

- **Módulo:** `src/archivos.c`, `include/archivos.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-16, RF-17, RNF-07 · CU-12

**Descripción.** Un archivo de texto por estructura en `datos/`. Se carga al iniciar y se guarda al registrar cambios y al salir.

**Criterios de aceptación.**
- [ ] Lo que se registra sigue ahí al cerrar y volver a abrir el programa.
- [ ] Si no existen los archivos, se crean vacíos con las categorías predeterminadas (Renta, Servicios, Súper, Limpieza, Otros).
- [ ] Si un archivo falta o está dañado, el programa avisa y continúa con datos vacíos.

#### ISS-06 · Registrar usuarios e iniciar sesión

- **Módulo:** `src/usuarios.c`, `include/usuarios.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-01, RF-02, RNF-08 · CU-01

**Descripción.** Alta de usuarios con nombre y PIN de 4 dígitos, e inicio de sesión eligiendo el usuario de una lista.

**Criterios de aceptación.**
- [ ] No se permiten nombres repetidos.
- [ ] Tras 3 PIN incorrectos se regresa a la lista de usuarios (E2).
- [ ] Si no hay usuarios, el primero que se registra queda como Administrador (E3).
- [ ] El PIN nunca aparece en pantalla en listados.

#### ISS-07 · Crear el menú principal

- **Módulo:** `src/main.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RNF-02

**Descripción.** El menú de la propuesta (§1.6) con `switch`. Las opciones que aún no existen muestran "Disponible en un próximo incremento".

**Criterios de aceptación.**
- [ ] Muestra el grupo activo y si el usuario es Administrador.
- [ ] La opción 0 guarda y sale.
- [ ] `main.c` solo llama a funciones de los módulos.

#### ISS-08 · Revisar el incremento 1 y etiquetar v0.1

- **Labels:** `tipo:test`

**Criterios de aceptación.**
- [ ] `make` compila sin advertencias.
- [ ] Se probaron las rutas alternativas de CU-01 y CU-12; los casos quedan en `tests/`.
- [ ] Se creó la etiqueta `v0.1` (`git tag v0.1` y `git push --tags`).

### Incremento 2 — Grupos

#### ISS-09 · Gestionar grupos

- **Módulo:** `src/grupos.c`, `include/grupos.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-03 · CU-09

**Criterios de aceptación.**
- [ ] El Administrador puede crear, renombrar y eliminar grupos.
- [ ] Se rechazan nombres vacíos o repetidos (E1).
- [ ] No se elimina un grupo con saldos pendientes (E2). *Se completa cuando exista el cálculo de saldos (ISS-19).*
- [ ] Al llegar a 5 grupos, el sistema avisa (E3).

#### ISS-10 · Gestionar miembros

- **Módulo:** `src/grupos.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-04 · CU-10

**Criterios de aceptación.**
- [ ] El Administrador agrega un usuario existente o uno nuevo, y quita miembros.
- [ ] Avisa si el usuario ya es miembro (E1) o si el grupo llegó a 10 miembros (E3).
- [ ] No se quita a un miembro con saldo distinto de cero (E2). *Se completa con ISS-19.*

#### ISS-11 · Gestionar categorías

- **Módulo:** `src/grupos.c` o un módulo propio si crece
- **Labels:** `tipo:feature` `prioridad:media`
- **Requerimientos:** RF-05 · CU-11

**Criterios de aceptación.**
- [ ] El Administrador agrega, renombra y elimina categorías.
- [ ] Se rechazan nombres vacíos o repetidos (E1).
- [ ] No se elimina una categoría con gastos asociados (E2). *Se completa con ISS-14.*

#### ISS-12 · Crear el menú de administración

- **Módulo:** `src/main.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RNF-08

**Criterios de aceptación.**
- [ ] La opción 7 del menú principal abre los submenús de grupos, miembros y categorías.
- [ ] Un Roomie que no es Administrador no puede entrar.
- [ ] La opción 6 permite cambiar el grupo activo.

#### ISS-13 · Revisar el incremento 2 y etiquetar v0.2

- **Labels:** `tipo:test`

**Criterios de aceptación.**
- [ ] `make` compila sin advertencias.
- [ ] Se probaron las rutas alternativas de CU-09, CU-10 y CU-11.
- [ ] Se creó la etiqueta `v0.2`.

### Incremento 3 — Gastos

#### ISS-14 · Registrar gasto

- **Módulo:** `src/gastos.c`, `include/gastos.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-06 · CU-02

**Criterios de aceptación.**
- [ ] Se capturan descripción, monto, fecha, categoría, pagador y participantes.
- [ ] Monto cero, negativo o no numérico se vuelve a pedir (E1); igual la fecha inválida (E2).
- [ ] Un participante que no es del grupo se rechaza (E3).
- [ ] Se muestra un resumen y, si se cancela, no se guarda nada (E4).
- [ ] Al llegar a 500 gastos, el sistema avisa (E5).

#### ISS-15 · Dividir gasto en partes iguales

- **Módulo:** `src/gastos.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-07, RNF-04 · CU-03

**Criterios de aceptación.**
- [ ] El monto en centavos se divide entre los participantes.
- [ ] El residuo se asigna al pagador, y la suma de las partes es exactamente el total.
- [ ] Ejemplo: $100.00 entre 3 → $33.34 (pagador), $33.33, $33.33.

#### ISS-16 · Dividir gasto en partes personalizadas

- **Módulo:** `src/gastos.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-08 · CU-03

**Criterios de aceptación.**
- [ ] Se captura la parte de cada participante.
- [ ] Si la suma no coincide con el total, se muestra la diferencia y se piden de nuevo (E1).
- [ ] Una parte negativa se rechaza (E2).

#### ISS-17 · Eliminar o corregir gasto

- **Módulo:** `src/gastos.c`
- **Labels:** `tipo:feature` `prioridad:media`
- **Requerimientos:** RF-09

**Criterios de aceptación.**
- [ ] Solo el pagador o el Administrador pueden eliminar un gasto.
- [ ] Se eliminan también sus divisiones y el cambio se guarda.

#### ISS-18 · Revisar el incremento 3 y etiquetar v0.3

- **Labels:** `tipo:test`

**Criterios de aceptación.**
- [ ] `make` compila sin advertencias.
- [ ] Se probaron las rutas alternativas de CU-02 y CU-03.
- [ ] Se completaron los criterios pendientes de ISS-11.
- [ ] Se creó la etiqueta `v0.3`.

### Incremento 4 — Saldos

#### ISS-19 · Calcular y consultar saldos

- **Módulo:** `src/saldos.c`, `include/saldos.h`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-10, RNF-04 · CU-04, CU-05

**Criterios de aceptación.**
- [ ] El saldo de cada miembro es lo pagado menos lo que le correspondía, ajustado por liquidaciones.
- [ ] La suma de los saldos del grupo es exactamente cero.
- [ ] Sin gastos, se muestra "No hay gastos registrados" y todos en $0.00 (E1).
- [ ] Se completan los criterios pendientes de ISS-09 e ISS-10.

#### ISS-20 · Simplificar deudas

- **Módulo:** `src/saldos.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-11 · CU-06

**Criterios de aceptación.**
- [ ] El algoritmo greedy empareja al mayor deudor con el mayor acreedor hasta que todos queden en cero.
- [ ] Con n miembros se generan como máximo n − 1 transferencias.
- [ ] El ejemplo de la propuesta (Luis +600, Ana −400, Beto −150, Caro −50) da exactamente 3 transferencias.
- [ ] Si todos están en cero, muestra "El grupo está a mano" (E1).

#### ISS-21 · Registrar liquidación

- **Módulo:** `src/saldos.c`
- **Labels:** `tipo:feature` `prioridad:alta`
- **Requerimientos:** RF-12 · CU-07

**Criterios de aceptación.**
- [ ] Se puede elegir una transferencia sugerida o capturarla a mano.
- [ ] Deudor y acreedor no pueden ser la misma persona (E1).
- [ ] Si el monto supera la deuda, se advierte y se pide confirmar (E2).
- [ ] Los saldos se actualizan y se guarda.

#### ISS-22 · Revisar el incremento 4 y etiquetar v0.4

- **Labels:** `tipo:test`

**Criterios de aceptación.**
- [ ] `make` compila sin advertencias.
- [ ] Se probaron las rutas alternativas de CU-04 a CU-07; la suma de saldos es cero en todos los casos.
- [ ] Se creó la etiqueta `v0.4`.

### Entrega final

#### ISS-23 · Mostrar el historial de gastos

- **Módulo:** `src/reportes.c`, `include/reportes.h`
- **Labels:** `tipo:feature` `prioridad:media`
- **Requerimientos:** RF-13 · CU-08

**Criterios de aceptación.**
- [ ] Muestra gastos y liquidaciones del grupo ordenados por fecha.
- [ ] Si no hay movimientos en el periodo, lo indica (E1).

#### ISS-24 · Generar el reporte por categoría

- **Módulo:** `src/reportes.c`
- **Labels:** `tipo:feature` `prioridad:media`
- **Requerimientos:** RF-14 · CU-08

**Criterios de aceptación.**
- [ ] Muestra el total y el porcentaje por categoría, como en el boceto de la propuesta.
- [ ] Filtra por mes (`mm/aaaa`) y rechaza formatos inválidos (E2).

#### ISS-25 · Generar el reporte por persona

- **Módulo:** `src/reportes.c`
- **Labels:** `tipo:feature` `prioridad:media`
- **Requerimientos:** RF-15 · CU-08

**Criterios de aceptación.**
- [ ] Muestra cuánto pagó y cuánto le correspondió a cada miembro.

#### ISS-26 · Ejecutar los casos de prueba completos

- **Carpeta:** `tests/`
- **Labels:** `tipo:test`
- **Requerimientos:** RNF-03, RNF-05

**Criterios de aceptación.**
- [ ] Hay casos con entradas válidas e inválidas para cada caso de uso (CU-01 a CU-12).
- [ ] Todas las operaciones responden en menos de 1 segundo con la capacidad máxima.
- [ ] Los errores encontrados tienen su issue `tipo:fix` y están corregidos.

#### ISS-27 · Escribir el manual de usuario

- **Archivo:** `docs/manuales/manual_usuario.md`
- **Labels:** `tipo:docs`

**Criterios de aceptación.**
- [ ] Explica cómo compilar, ejecutar y usar cada opción del menú, con ejemplos de pantalla.

#### ISS-28 · Integrar y publicar la versión 1.0

- **Labels:** `tipo:chore`

**Criterios de aceptación.**
- [ ] `make` compila sin advertencias en una copia limpia del repositorio.
- [ ] No queda código comentado ni de prueba.
- [ ] El README está actualizado.
- [ ] Se creó la etiqueta `v1.0` y un *Release* en GitHub.
