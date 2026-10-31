# Sistema de Control Académico — Grupo 3 (UMG · Algoritmos)

Programa de consola en C++ para registrar estudiantes, cursos y notas, calcular promedios,
determinar aprobación y consultar reportes. Los datos se guardan en archivos de texto.

## Módulos

| # | Módulo | Archivos | Responsabilidad |
|---|--------|----------|-----------------|
| 1 | Estudiantes | `estudiantes.h/.cpp` | Registrar, editar, buscar (carné y nombre parcial), listar, contar (recursivo), validar carné |
| 2 | Cursos y Notas | `cursos_notas.h/.cpp` | Registrar cursos, registrar y modificar notas con validación de rango y existencia |
| 3 | Reportes | `src/reportes.h/.cpp` | Expediente por carné, promedio por curso, aprobados/reprobados, mejor promedio, matriz |
| 4 | Procesamiento | `procesamiento.h/.cpp` | Promedios, umbral y resultado de aprobación, conteos recursivos, matriz estudiante × curso |
| 5 | Persistencia | `persistencia.h/.cpp` | Cargar y guardar `estudiantes.txt`, `cursos.txt`, `notas.txt` |

Base compartida: `estructuras.h` (struct y capacidades) y `Main.cpp` (menú principal e integración).

## Estructura de carpetas

```
sistema-control-academico/
├── Main.cpp
├── estructuras.h
├── estudiantes.h / estudiantes.cpp
├── cursos_notas.h / cursos_notas.cpp
├── procesamiento.h / procesamiento.cpp
├── persistencia.h / persistencia.cpp
├── src/reportes.h / reportes.cpp
├── pruebas/pruebas.cpp
├── docs/diagramas_de_flujo.md
└── .vscode/tasks.json
```

## Compilar y ejecutar (VS Code)

1. `Ctrl+Shift+B` → **Compilar sistema completo** → genera `sistema.exe`.
2. Ejecutar `.\sistema.exe`.
3. Pruebas: tarea **Compilar pruebas** → ejecutar `.\pruebas.exe` (56 comprobaciones).

Compilación manual: 

```
g++ -std=c++17 -Wall -Wextra -I. -Isrc Main.cpp estudiantes.cpp cursos_notas.cpp procesamiento.cpp persistencia.cpp src/reportes.cpp -o sistema.exe
```

## Formato de archivos de datos

Un registro por línea, campos separados por `|`:

- `estudiantes.txt` → `carnet|nombre|apellido`
- `cursos.txt` → `codigo|nombre|notaMinima`
- `notas.txt` → `carnet|codigoCurso|nota`

Si un archivo no existe, el sistema arranca vacío. Las líneas dañadas y las notas que apuntan a
un estudiante o curso inexistente se omiten al cargar.

## Reglas del sistema

- Nota válida: de 0 a 100. No se registran notas de estudiantes o cursos inexistentes.
- Una sola nota por estudiante y curso (para cambiarla se usa «Modificar notas»).
- Carné con formato `####-##-#####` (tres grupos de dígitos separados por guion).
- Aprobación: promedio del estudiante ≥ promedio de las notas mínimas de los cursos en que tiene nota.
- Estudiantes sin notas no cuentan como aprobados ni reprobados, ni en el promedio general.
- Todos los promedios se calculan desde los datos cargados; nada queda fijo en el código.

## Flujo de trabajo Git

Cada integrante trabaja en su rama (`feature/<modulo>`), abre un Pull Request hacia `main`, otro
integrante lo revisa y recién entonces se fusiona. Después de fusionar todo: clonar `main` desde
cero, compilar y ejecutar las pruebas.
