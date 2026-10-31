#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <string>
#include "estructuras.h"

// Suma RECURSIVAMENTE las notas de un estudiante especifico dentro del arreglo de notas.
// Caso base: indice == totalNotas. Caso recursivo: revisa el registro actual y avanza.
double sumarNotasRecursivo(const RegistroNota notas[], int totalNotas, const std::string &carnet, int indice);

// Cuenta RECURSIVAMENTE cuantos registros de nota tiene un estudiante.
int contarNotasEstudianteRecursivo(const RegistroNota notas[], int totalNotas, const std::string &carnet, int indice);

// Calcula el promedio de todas las notas de un estudiante (usa las funciones recursivas de arriba).
// Devuelve 0 si el estudiante no tiene notas registradas.
double calcularPromedioEstudiante(const std::string &carnet, const RegistroNota notas[], int totalNotas);

// Calcula el promedio de un estudiante SOLO en un curso especifico.
double calcularPromedioEstudianteEnCurso(const std::string &carnet, const std::string &codigoCurso,
                                          const RegistroNota notas[], int totalNotas);

// Determina "APROBADO" o "REPROBADO" comparando el promedio contra el umbral del curso (no un valor fijo).
std::string determinarResultado(double promedio, double notaMinimaAprobacion);

// Cuenta RECURSIVAMENTE cuantos estudiantes tienen promedio general >= su nota minima promedio de cursos cursados.
// (Se usa para las estadisticas del reporte general.)
int contarAprobadosRecursivo(const Estudiante estudiantes[], int totalEstudiantes,
                              const RegistroNota notas[], int totalNotas,
                              const Curso cursos[], int totalCursos, int indice);

// Calcula el promedio general de todo el grupo (promedio de los promedios de cada estudiante).
double calcularPromedioGeneral(const Estudiante estudiantes[], int totalEstudiantes,
                                const RegistroNota notas[], int totalNotas);

// Construye una matriz estudiante x curso con las notas (0 si el estudiante no tiene nota en ese curso).
// 'matriz' debe tener tamano [MAX_ESTUDIANTES][MAX_CURSOS] reservado por quien la llama.
void construirMatrizCalificaciones(const Estudiante estudiantes[], int totalEstudiantes,
                                    const Curso cursos[], int totalCursos,
                                    const RegistroNota notas[], int totalNotas,
                                    double matriz[][MAX_CURSOS]);

// Devuelve el indice (en 'estudiantes') de quien tiene el mejor promedio general. -1 si no hay datos.
int indiceEstudianteConMayorPromedio(const Estudiante estudiantes[], int totalEstudiantes,
                                      const RegistroNota notas[], int totalNotas);

// Promedio de todas las notas de un curso. 0 si el curso no tiene notas.
double calcularPromedioCurso(const std::string &codigoCurso, const RegistroNota notas[], int totalNotas);

// Umbral de aprobacion de un estudiante: promedio de las notas minimas de los cursos donde tiene nota.
// 0 si el estudiante no tiene notas.
double calcularUmbralEstudiante(const std::string &carnet, const RegistroNota notas[], int totalNotas,
                                 const Curso cursos[], int totalCursos);

// Cuenta RECURSIVAMENTE cuantos estudiantes tienen al menos una nota registrada.
int contarEstudiantesConNotasRecursivo(const Estudiante estudiantes[], int totalEstudiantes,
                                        const RegistroNota notas[], int totalNotas, int indice);

#endif
