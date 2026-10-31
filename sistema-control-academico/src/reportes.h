#ifndef REPORTES_H
#define REPORTES_H

#include <string>
#include "estructuras.h"

// Funciones de impresión y reportes
void mostrarEncabezado();
void mostrarReporteEstudiante(std::string nombreCompleto, double promedio, std::string resultado);
void mostrarReporteGeneral(int total, int aprobados, int reprobados, double promedioGeneral);
void mostrarExpedienteEstudiante(const Estudiante estudiantes[], int totalEst, 
                                  const RegistroNota notas[], int totalNotas,
                                  const Curso cursos[], int totalCursos, 
                                  std::string busqueda);


// Menu interactivo del modulo de Reportes y Consultas. Se llama desde main().
void menuReportes(const Estudiante estudiantes[], int totalEstudiantes,
                  const Curso cursos[], int totalCursos,
                  const RegistroNota notas[], int totalNotas);

#endif