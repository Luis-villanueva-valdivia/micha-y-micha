# Casos de prueba · Incremento 3 (v0.3)

- **Issue:** ISS-18 · Revisar el incremento 3 y etiquetar v0.3
- **Fecha:** 15/11/2026
- **Versión probada:** `main` en `e81225a` (merge del PR #43)
- **Compilación:** `make clean && make` → 0 advertencias

Escenario: Luis (PIN `1234`) es el Administrador. En el grupo "Depa Centro" están
Luis, Ana (`1111`), Beto (`2222`) y Caro (`3333`). Cada caso se ejecuta con
`./michaymicha` escribiendo las entradas en orden desde el menú principal
(opción 1 → Gastos).

## CU-02 · Registrar gasto (opción 1 → 1)

| ID | Ruta | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| Q01 | Flujo principal | `Luz noviembre`, `840.50`, `05/11/2026`, Servicios, pagó Luis, todos, iguales, `1` | Se guarda el gasto y una división por participante | "Gasto registrado." · `gastos.txt` = `1\|1\|1\|2\|Luz noviembre\|84050\|20261105\|0` · 4 divisiones | ✅ |
| Q02 | E1 · Monto inválido | `abc`, `0`, `-5`, luego `100` | Vuelve a pedir el monto | "Error: Ingrese un monto mayor que 0:" (3 veces) | ✅ |
| Q03 | E2 · Fecha inválida | `31/02/2026`, `15-11-2026`, luego `15/11/2026` | Vuelve a pedir la fecha | "Error: Ingrese una fecha valida (dd/mm/aaaa):" (2 veces) | ✅ |
| Q04 | E4 · Cancelar en el resumen | `0` al confirmar | No se guarda nada | "Gasto cancelado; no se guardo nada." · `gastos.txt` sigue con 1 gasto | ✅ |
| Q05 | E3 · Participantes | Uno por uno: `0` sin elegir, `9`, `2`, `2`, `3`, `0` | Pide al menos uno, rechaza fuera de rango y repetidos | "Debe haber al menos un participante." · "Ingrese un numero entre 0 y 4" · "Ese miembro ya esta en la lista." · quedan Ana y Beto | ✅ |
| Q06 | E5 · Máximo de gastos | `gastos.txt` con 500 gastos | Avisa antes de pedir datos | "Error: Ya se alcanzo el maximo de 500 gastos." | ✅ |
| Q07 | Sin grupo activo | Usuario sin grupos: `1` | Pide elegir un grupo | "Primero elige un grupo activo (opcion 6)." | ✅ |

## CU-03 · Dividir gasto (RF-07, RF-08)

| ID | Ruta | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| Q08 | Partes iguales con residuo | $840.50 entre 4, pagó Luis | El residuo va al pagador y la suma es exacta | Luis $210.14 · Ana, Beto y Caro $210.12 (suma $840.50) | ✅ |
| Q09 | Partes iguales exactas | $300.00 entre Ana y Beto | $150.00 cada uno | $150.00 · $150.00 | ✅ |
| Q10 | Personalizada · E1 suma distinta | $6000.00: `3000`, `2000`, `500`, `100` | Muestra la diferencia y pide todas de nuevo | "Las partes suman $5600.00 y la diferencia con el total es $400.00." | ✅ |
| Q11 | Personalizada · E2 parte negativa o en cero | `-1`, `0` | Rechaza la parte | "Error: Ingrese un monto mayor que 0:" | ✅ |
| Q12 | Personalizada correcta | `3000`, `1500`, `1000`, `500` | Se guarda con tipo personalizado | `tipoDivision` = 1 · divisiones 300000, 150000, 100000, 50000 | ✅ |
| Q13 | Un solo participante | Ana sola | No pregunta el tipo de división | No aparece "Como se divide el gasto" · Ana $45.00 | ✅ |

## RF-09 · Eliminar gasto (opción 1 → 2)

| ID | Ruta | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| Q14 | Roomie elimina gasto ajeno | Ana: gasto de Luis | Se le niega | "Error: Solo quien pago el gasto o el Administrador puede eliminarlo." | ✅ |
| Q15 | Confirmación "no" | Ana: su gasto, `0` | No elimina | "No se elimino el gasto." | ✅ |
| Q16 | Roomie elimina su gasto | Ana: su gasto, `1` | Elimina el gasto y sus divisiones | "Gasto eliminado." · sin divisiones del gasto 4 | ✅ |
| Q17 | Administrador elimina cualquiera | Luis: "Cena" | Elimina el gasto y sus divisiones | "Gasto eliminado." · sin divisiones del gasto 2 | ✅ |
| Q18 | Persistencia | Salir y volver a entrar | La lista refleja los cambios | Quedan "Luz noviembre" y "Renta" | ✅ |

## Hallazgos

1. **Residuo de varios centavos.** Cuando sobra más de un centavo (por ejemplo $840.50 entre 4 deja 2), todos se le asignan al pagador. Cumple RF-07 tal como se definió; si se quiere repartir un centavo por persona, sería un cambio de diseño.
2. **Corregir un gasto.** No hay edición directa: para corregir un gasto se elimina y se registra de nuevo. Queda documentado así para RF-09.
3. **Orden de la lista.** Al eliminar, los gastos se muestran en el orden en que se registraron, no por fecha. El historial ordenado por fecha se hace en ISS-23.
4. **EOF en las lecturas.** Igual que en los incrementos anteriores.

## Resultado

18 de 18 casos pasan. Sin correcciones necesarias en este incremento.
