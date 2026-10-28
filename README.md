# Micha y Micha

**Cuentas claras entre roomies.** Programa de consola en C para que un grupo de roomies registre y divida sus gastos compartidos, consulte el saldo de cada quien y sepa qué transferencias hacer para quedar a mano, con el menor número posible.

Proyecto final de Programación Estructurada — Facultad de Matemáticas, UADY.

## Autor

| Integrante | GitHub |
|---|---|
| Luis Adrián Villanueva Valdivia | [@Luis-villanueva-valdivia](https://github.com/Luis-villanueva-valdivia) |

## Tecnologías

Lenguaje C (estándar C99), compilado con GCC. Sin librerías externas, solo la biblioteca estándar (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`).

Temas del curso que se aplican: arreglos, estructuras, apuntadores, funciones y modularidad, condicionales, ciclos y manejo de archivos.

## Requisitos

- GCC (en Windows: [MinGW-w64](https://www.mingw-w64.org/) o el que trae Code::Blocks / Dev-C++)
- Git
- Opcional: `make`

## Compilar y ejecutar

1. **Clonar** el repositorio:
   ```bash
   git clone https://github.com/Luis-villanueva-valdivia/micha-y-micha.git
   cd micha-y-micha
   ```
2. **Compilar** con `make`:
   ```bash
   make
   ```
   o, sin `make`, directamente con GCC:
   ```bash
   gcc -Wall -Wextra -std=c99 -Iinclude src/*.c -o michaymicha
   ```
3. **Ejecutar**:
   ```bash
   ./michaymicha       # Linux / macOS / Git Bash
   michaymicha.exe     # Windows (CMD o PowerShell)
   ```

> Los ejecutables y archivos compilados están en `.gitignore` y nunca se suben al repositorio.

## Estructura

```
micha-y-micha/
├── src/          # archivos .c: main.c y un módulo por tema
├── include/      # archivos .h: estructuras, constantes y prototipos de cada módulo
├── datos/        # archivos que el programa guarda y lee (no se suben)
├── docs/         # propuesta, planeación, diagramas, manuales y convenciones
├── tests/        # casos de prueba con entrada y salida esperada
└── Makefile      # compila todo con un solo comando
```

## Documentación

- [Propuesta del proyecto](docs/propuesta/VillanuevaLuis_Propuesta.pdf): requerimientos, casos de uso y estándar de codificación.
- [Planeación](docs/planeacion/planeacion.md): milestones, issues y criterios de aceptación.
- [Convenciones](docs/convenciones.md): commits, ramas y resumen del estándar de codificación.

## Incrementos

| Incremento | Fecha límite | Etiqueta |
|---|---|---|
| 1 — Base | vie 30/10/2026 | `v0.1` |
| 2 — Grupos | lun 02/11/2026 | `v0.2` |
| 3 — Gastos | jue 05/11/2026 | `v0.3` |
| 4 — Saldos | lun 09/11/2026 | `v0.4` |
| Entrega final | mié 11/11/2026 | `v1.0` |
