#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "estructuras.h"


const char *const ARCHIVO_ESTUDIANTES = "estudiantes.txt";
const char *const ARCHIVO_CURSOS = "cursos.txt";
const char *const ARCHIVO_NOTAS = "notas.txt";


bool inicializarDatos(Estudiante estudiantes[], int &totalEstudiantes,
                      Curso cursos[], int &totalCursos,
                      RegistroNota notas[], int &totalNotas);

// Guarda los tres arreglos en sus archivos. Devuelve false si algun archivo no se pudo escribir.
bool guardarProgreso(const Estudiante estudiantes[], int totalEstudiantes,
                     const Curso cursos[], int totalCursos,
                     const RegistroNota notas[], int totalNotas);

#endif
