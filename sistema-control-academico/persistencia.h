#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "estructuras.h"

// Nombres de los archivos de datos (se crean junto al ejecutable).
//   estudiantes.txt -> carnet|nombre|apellido
//   cursos.txt      -> codigo|nombre|notaMinima
//   notas.txt       -> carnet|codigoCurso|nota
const char *const ARCHIVO_ESTUDIANTES = "estudiantes.txt";
const char *const ARCHIVO_CURSOS = "cursos.txt";
const char *const ARCHIVO_NOTAS = "notas.txt";

// Carga los tres archivos a los arreglos. Si un archivo no existe se toma como vacio (primera ejecucion).
// Las lineas danadas y las notas que apuntan a un estudiante o curso inexistente se omiten,
// para mantener relaciones consistentes. Los totales siempre quedan inicializados.
// Devuelve false solo si un archivo existe pero no se pudo leer.
bool inicializarDatos(Estudiante estudiantes[], int &totalEstudiantes,
                      Curso cursos[], int &totalCursos,
                      RegistroNota notas[], int &totalNotas);

// Guarda los tres arreglos en sus archivos. Devuelve false si algun archivo no se pudo escribir.
bool guardarProgreso(const Estudiante estudiantes[], int totalEstudiantes,
                     const Curso cursos[], int totalCursos,
                     const RegistroNota notas[], int totalNotas);

#endif
