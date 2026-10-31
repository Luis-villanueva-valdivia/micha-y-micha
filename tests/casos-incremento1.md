# Casos de prueba · Incremento 1 (v0.1)

- **Issue:** ISS-08 · Revisar el incremento 1 y etiquetar v0.1
- **Fecha:** 30/10/2026
- **Versión probada:** `main` en `a41101b` (merge del PR #33)
- **Compilación:** `make clean && make` → 0 advertencias

Cada caso se puede repetir así: se borra `datos/*.txt` cuando el caso lo pide,
se ejecuta `./michaymicha` y se escriben las entradas en orden.

## CU-01 · Iniciar sesión

| ID | Ruta | Estado inicial | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|---|
| P01 | E3 · No hay usuarios | `datos/` vacío | `Luis`, `1234`, `0` | Pide registrar al Administrador; Luis queda como Administrador y se guarda | "No hay usuarios. Registra al Administrador." · lista `1. Luis (Administrador)` · `usuarios.txt` = `1\|Luis\|1234\|1` | ✅ |
| P02 | Flujo principal | Luis registrado | `1`, `1234` | "Bienvenido, Luis." y menú principal con `[Admin]` | Igual | ✅ |
| P03 | E1 · Número inexistente | Luis registrado | `5`, `abc`, `1`, `1234` | Error y vuelve a pedir el número | "Error: Ingrese un numero entre 0 y 1" dos veces; luego entra | ✅ |
| P04 | E2 · PIN incorrecto (3 veces) | Luis registrado | `1`, `1111`, `2222`, `3333` | Avisa en cada intento; tras 3 regresa a la lista | "Te quedan 2… 1… 0 intentos" · "Demasiados intentos. Regresando a la lista." · se muestra la lista otra vez | ✅ |
| P05 | E2 · Reintento tras regresar | Después de P04 | `1`, `1234` | Puede entrar en el siguiente intento | "Bienvenido, Luis." | ✅ |
| P06 | Salir sin iniciar sesión | Luis registrado | `0` | Sale sin entrar | "Hasta luego." | ✅ |
| P07 | Validación de PIN al registrar | `datos/` vacío | `Luis`, `123`, `12345`, `ab12`, `1234` | Rechaza los tres primeros PIN | "El PIN debe tener exactamente 4 digitos" tres veces; acepta `1234` | ✅ |
| P08 | PIN fuera de los listados | Varios usuarios | — | El PIN nunca aparece en la lista de usuarios | La lista solo muestra número, nombre y `(Administrador)` | ✅ |

## Menú principal (ISS-07)

| ID | Caso | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| P09 | Grupo activo y rol | Entrar como Luis | `Grupo: Ninguno   [Admin]` | Igual | ✅ |
| P10 | Opciones no implementadas | `3` | "Disponible en un proximo incremento." y vuelve al menú | Igual | ✅ |
| P11 | Opción fuera de rango | `9` | Error y vuelve a pedir | "Error: Ingrese un numero entre 0 y 7" | ✅ |

## CU-12 · Guardar datos

| ID | Ruta | Estado inicial | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|---|
| P12 | Flujo principal | Luis registrado | Entrar y elegir `0` | Se escriben los 7 archivos de `datos/` | Se crean `usuarios`, `grupos`, `miembros`, `categorias`, `gastos`, `divisiones` y `liquidaciones.txt` | ✅ |
| P13 | Los datos persisten | Después de P12 | Volver a ejecutar | Ya no pide registrar al Administrador; Luis aparece en la lista | Igual | ✅ |
| P14 | Registrar y salir en el inicio de sesión | `datos/` vacío | `Ana`, `1111`, `0` | Ana queda guardada | `usuarios.txt` = `1\|Ana\|1111\|1` | ✅ |
| P15 | E1 · No se puede escribir un archivo | `datos/usuarios.txt` reemplazado por una carpeta | Entrar y elegir `0` | Muestra un aviso, conserva los datos en memoria y **permite reintentar** | Muestra "Error: no se pudieron guardar los usuarios." pero enseguida dice "Datos guardados. Hasta luego." y **sale sin permitir reintentar** | ❌ |
| P16 | E1 · Falta la carpeta `datos/` | Sin carpeta `datos/` | Entrar y elegir `0` | Igual que P15 | Muestra los 7 errores, dice "Datos guardados" y sale; no se guarda nada | ❌ |

## Hallazgos

1. **CU-12 E1 no permite reintentar (P15, P16).** Si algún `guardar…()` falla, el programa avisa pero sale de todos modos y se pierde lo que estaba en memoria. Además el mensaje "Datos guardados" sale aunque haya fallado. Se registra como issue `tipo:fix` para corregirlo en el incremento 2.
2. **EOF en las lecturas (limitación conocida del ISS-04).** Si la entrada se termina (Ctrl+Z o un archivo de entradas incompleto), `leerTexto` y `leerEntero` se quedan en un ciclo infinito. No afecta el uso normal en consola.
3. **Detalle de texto (P04).** Al tercer fallo se muestra "Te quedan 0 intentos" justo antes de "Demasiados intentos". Es solo cosmético.

## Resultado

14 de 16 casos pasan. Las rutas alternativas de CU-01 (E1, E2, E3) funcionan completas. De CU-12 funciona el flujo principal; la ruta E1 queda pendiente como fix.