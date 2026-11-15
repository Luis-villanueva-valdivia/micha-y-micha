# Casos de prueba · Incremento 4 (v0.4)

- **Issue:** ISS-22 · Revisar el incremento 4 y etiquetar v0.4
- **Fecha:** 15/11/2026
- **Versión probada:** `main` en `4b353ba` (merge del PR #47)
- **Compilación:** `make clean && make` → 0 advertencias

Escenario: Luis (PIN `1234`) es el Administrador. Grupos "Depa Centro" (Luis,
Ana `1111` y Beto `2222`) y "Casa Playa" (solo Luis). Gastos de "Depa Centro":
"Luz" $840.50 pagado por Luis entre los tres, partes iguales; "Cena" $300.00
pagado por Ana entre Ana y Beto, partes iguales.

## CU-04 · Consultar saldos (opción 2)

| ID | Ruta | Estado | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| R01 | Sin gastos | Grupo nuevo | Todos al corriente | Luis, Ana y Beto `$0.00 al corriente` · Suma `$0.00` | ✅ |
| R02 | Con gastos | Luz + Cena | Saldo = lo que pagó − lo que le toca | Luis `$560.32 le deben` · Ana `-$130.16 debe` · Beto `-$430.16 debe` | ✅ |
| R03 | Suma de saldos (RNF-04) | Luz + Cena | La suma es exactamente cero | `Suma de saldos: $0.00` | ✅ |
| R04 | Roomie consulta | Ana: `2` | Ve la tabla de su grupo | Muestra "Saldos del grupo" | ✅ |

Comprobación a mano: Luz $840.50 / 3 = $280.16 con 2 centavos de residuo para Luis ($280.18). Luis: 840.50 − 280.18 = 560.32. Ana: 300.00 − 280.16 − 150.00 = −130.16. Beto: −280.16 − 150.00 = −430.16.

## CU-05 · Simplificar deudas (opción 3)

| ID | Ruta | Estado | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| R05 | Sin deudas | Grupo nuevo | Lo indica | "No hay deudas pendientes." | ✅ |
| R06 | Con deudas | Luz + Cena | Pagos mínimos (n − 1 como máximo) | "1. Beto le paga $430.16 a Luis" · "2. Ana le paga $130.16 a Luis" | ✅ |

## CU-06 · Registrar liquidación (opción 4)

| ID | Ruta | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| R07 | Sin deudas | `4` | No pide datos | "No hay deudas pendientes." | ✅ |
| R08 | Monto mayor a lo que se debe | Pago 1, `500` | Lo rechaza | "Error: El monto no puede ser mayor a lo que se debe:" | ✅ |
| R09 | Cancelar | Pago 1, `200`, fecha, `0` | No guarda | "No se registro el pago." | ✅ |
| R10 | Pago parcial | Pago 1, `200`, `07/11/2026`, `1` | Se guarda y la sugerencia baja | "Pago registrado." · ahora "Beto le paga $230.16 a Luis" | ✅ |
| R11 | Saldar todo | `230.16` de Beto y `130.16` de Ana | Todos en cero | Los tres `$0.00 al corriente` · "No hay deudas pendientes." · 3 líneas en `liquidaciones.txt` | ✅ |

## E2 de CU-09 y CU-10 (opción 7)

| ID | Ruta | Entradas | Resultado esperado | Resultado obtenido | ¿Pasa? |
|---|---|---|---|---|---|
| R12 | Eliminar grupo con saldos | Grupos → `3`, "Depa Centro" | No lo elimina | "Error: El grupo tiene saldos pendientes; primero liquiden las deudas." | ✅ |
| R13 | Quitar miembro con saldo | Miembros → `2`, Beto | No lo quita | "Error: El miembro tiene saldo distinto de cero; primero debe liquidar." | ✅ |
| R14 | Eliminar grupo sin saldos | Grupos → `3`, "Casa Playa", `1` | Lo elimina | "Grupo eliminado." | ✅ |
| R15 | Quitar miembro ya saldado | Después de R11, quitar a Beto | Lo quita | "Miembro quitado del grupo." | ✅ |

## Hallazgos

1. **Historial de un miembro que sale.** Al quitar a un miembro ya saldado, sus gastos y divisiones anteriores siguen en los archivos; como su saldo es cero, no afecta los saldos del grupo.
2. **EOF en las lecturas.** Igual que en los incrementos anteriores.

## Resultado

15 de 15 casos pasan. Los E2 que quedaron pendientes en el incremento 2 ya están cubiertos.
