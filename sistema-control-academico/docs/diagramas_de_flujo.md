# Diagramas de flujo — Sistema de Control Académico

Los diagramas están en formato Mermaid. Se pueden ver en GitHub (se dibujan solos) o pegando el
código en https://mermaid.live para exportarlos como imagen y ponerlos en el informe.

## 1. Diagrama general (Main.cpp)

```mermaid
flowchart TD
    A([Inicio]) --> B[inicializarDatos: leer estudiantes.txt, cursos.txt, notas.txt]
    B --> C[/Mostrar menú principal/]
    C --> D[/Leer opción/]
    D --> E{Opción}
    E -- 1 --> F[menuEstudiantes] --> G[guardarProgreso]
    E -- 2 --> H[menuCursosNotas] --> G
    E -- 3 --> I[menuReportes]
    E -- 0 --> J[guardarProgreso] --> K([Fin])
    E -- otra --> L[/Opción inválida/]
    G --> C
    I --> C
    L --> C
```

## 2. Módulo Estudiantes

```mermaid
flowchart TD
    A([menuEstudiantes]) --> B[/Mostrar menú y leer opción/]
    B --> C{Opción}
    C -- 1 Registrar --> D[/Leer carnet, nombre, apellido/]
    D --> E{¿Formato de carné válido, datos completos, sin duplicado y con espacio?}
    E -- Sí --> F[Guardar estudiante en el arreglo] --> G[/Registrado/]
    E -- No --> H[/No se pudo registrar/]
    C -- 2 Editar --> I[/Leer carnet y nuevos datos/] --> J{¿Existe el carné?}
    J -- Sí --> K[Actualizar nombre y apellido]
    J -- No --> L[/No se encontró/]
    C -- 3 Buscar por carné --> M[buscarEstudiantePorCarnet] --> N[/Mostrar o No encontrado/]
    C -- 4 Buscar por nombre --> O[buscarEstudiantesPorNombre: coincidencia parcial] --> P[/Mostrar coincidencias/]
    C -- 5 Listar --> Q[listarEstudiantes: recorrer arreglo]
    C -- 6 Contar --> R[contarEstudiantesRecursivo] --> S[/Mostrar total/]
    C -- 0 --> T([Volver al menú principal])
    G --> B
    H --> B
    K --> B
    L --> B
    N --> B
    P --> B
    Q --> B
    S --> B
```

## 3. Módulo Cursos y Notas

```mermaid
flowchart TD
    A([menuCursosNotas]) --> B[/Mostrar menú y leer opción/]
    B --> C{Opción}
    C -- 1 Registrar curso --> D[/Leer código, nombre, nota mínima/]
    D --> E{¿Código válido y sin duplicado, nombre no vacío, mínima entre 0 y 100, hay espacio?}
    E -- Sí --> F[Guardar curso] --> G[/Curso registrado/]
    E -- No --> H[/No se pudo registrar/]
    C -- 2 Listar --> I[listarCursos]
    C -- 3 Registrar nota --> J[/Leer carné, código, nota/]
    J --> K{¿Nota entre 0 y 100?}
    K -- No --> Z[/No se pudo registrar/]
    K -- Sí --> L{¿Existe el estudiante?}
    L -- No --> Z
    L -- Sí --> M{¿Existe el curso?}
    M -- No --> Z
    M -- Sí --> N{¿Ya existe nota para ese estudiante y curso?}
    N -- Sí --> Z
    N -- No --> O[Guardar nota] --> P[/Nota registrada/]
    C -- 4 Modificar nota --> Q[/Leer carné, código, nueva nota/]
    Q --> R{¿Nota válida y registro existente?}
    R -- Sí --> S[Actualizar nota] --> T[/Nota actualizada/]
    R -- No --> U[/No se encontró o valor inválido/]
    C -- 0 --> V([Volver al menú principal])
    G --> B
    H --> B
    I --> B
    P --> B
    Z --> B
    T --> B
    U --> B
```

## 4. Módulo Procesamiento

```mermaid
flowchart TD
    A([Entrada: estudiantes, cursos, notas]) --> B[calcularPromedioEstudiante]
    B --> B1[contarNotasEstudianteRecursivo]
    B --> B2[sumarNotasRecursivo]
    B1 --> B3{¿Cantidad = 0?}
    B3 -- Sí --> B4[/Promedio = 0/]
    B3 -- No --> B5[/Promedio = suma / cantidad/]
    A --> C[calcularUmbralEstudiante: promedio de las notas mínimas de sus cursos]
    B5 --> D[determinarResultado]
    C --> D
    D --> E{¿Promedio ≥ umbral?}
    E -- Sí --> F[/APROBADO/]
    E -- No --> G[/REPROBADO/]
    A --> H[contarAprobadosRecursivo: por cada estudiante con notas, comparar promedio y umbral]
    A --> I[calcularPromedioCurso: contar y sumar notas del curso recursivamente]
    A --> J[calcularPromedioGeneral: promedio de promedios, solo estudiantes con notas]
    A --> K[construirMatrizCalificaciones: recorrer filas y columnas]
    A --> L[indiceEstudianteConMayorPromedio: recorrido buscando el máximo]
```

## 5. Módulo Reportes

```mermaid
flowchart TD
    A([menuReportes]) --> B[/Mostrar menú y leer opción/]
    B --> C{Opción}
    C -- 1 Expediente --> D[/Leer carné/] --> E{¿Existe el estudiante?}
    E -- No --> F[/No existe/]
    E -- Sí --> G{¿Tiene notas?}
    G -- No --> H[/Sin notas registradas/]
    G -- Sí --> I[Listar notas por curso con estado] --> J[Calcular promedio, umbral y resultado] --> K[/Reporte del estudiante/]
    C -- 2 Promedio por curso --> L[Recorrer cursos y calcular promedio de cada uno] --> M[/Tabla de promedios/]
    C -- 3 Aprobados y reprobados --> N[Contar con notas, aprobados y calcular promedio general] --> O[/Reporte general/]
    C -- 4 Mayor promedio --> P[indiceEstudianteConMayorPromedio] --> Q[/Mostrar estudiante o aviso de sin datos/]
    C -- 5 Matriz --> R[construirMatrizCalificaciones] --> S[/Mostrar matriz estudiante x curso/]
    C -- 0 --> T([Volver al menú principal])
    F --> B
    H --> B
    K --> B
    M --> B
    O --> B
    Q --> B
    S --> B
```

## 6. Módulo Persistencia

```mermaid
flowchart TD
    A([inicializarDatos]) --> B[Totales en 0]
    B --> C{¿Existe estudiantes.txt?}
    C -- Sí --> D[Leer cada línea, dividir por pipe y registrar estudiante válido]
    C -- No --> E[Arreglo vacío]
    D --> F{¿Existe cursos.txt?}
    E --> F
    F -- Sí --> G[Leer cada línea y registrar curso válido]
    F -- No --> H[Arreglo vacío]
    G --> I{¿Existe notas.txt?}
    H --> I
    I -- Sí --> J[Leer cada línea y registrar nota solo si existen estudiante y curso]
    I -- No --> K[Arreglo vacío]
    J --> L([Datos cargados])
    K --> L

    M([guardarProgreso]) --> N[Escribir estudiantes.txt]
    N --> O[Escribir cursos.txt]
    O --> P[Escribir notas.txt]
    P --> Q{¿Todo se escribió bien?}
    Q -- Sí --> R([Devuelve true])
    Q -- No --> S([Devuelve false])
```
