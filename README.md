# Micha y Micha

Programa de consola en C que ayuda a los roomies a llevar las cuentas de la casa: registrar quién vive en el departamento, anotar los gastos compartidos y calcular cuánto le debe cada quien a quién.

Proyecto final de Programación Estructurada — Facultad de Matemáticas, UADY.

## Autor

| Integrante | GitHub |
|---|---|
| Luis Adrián Villanueva Valdivia | [@Luis-villanueva-valdivia](https://github.com/Luis-villanueva-valdivia) |

## Tecnologías

Lenguaje C (estándar C11), compilado con GCC. Sin librerías externas, solo la biblioteca estándar (`stdio.h`, `stdlib.h`, `string.h`).

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
   gcc -Wall -Wextra -std=c11 -Iinclude src/*.c -o micha
   ```
3. **Ejecutar**:
   ```bash
   ./micha        # Linux / macOS / Git Bash
   micha.exe      # Windows (CMD o PowerShell)
   ```

> Los ejecutables y archivos compilados están en `.gitignore` y nunca se suben al repositorio.

## Estructura

```
micha-y-micha/
├── src/          # archivos .c: main.c y un módulo por tema
├── include/      # archivos .h: estructuras, constantes y prototipos de cada módulo
├── data/         # archivos que el programa guarda y lee (no se suben)
├── docs/         # propuesta, diagramas, manuales y convenciones
├── tests/        # casos de prueba con entrada y salida esperada
└── Makefile      # compila todo con un solo comando
```

## Convenciones

Commits, ramas, nombres y estándares de código: [docs/convenciones.md](docs/convenciones.md).

## Fechas

| Entrega | Fecha |
|---|---|
| Entrega final | mié 11/11/2026 |
