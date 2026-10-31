#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>

// Capacidades definidas de los arreglos del sistema.
const int MAX_ESTUDIANTES = 100;
const int MAX_CURSOS = 20;
const int MAX_NOTAS = MAX_ESTUDIANTES * MAX_CURSOS; // una nota por estudiante-curso

struct Estudiante
{
    std::string carnet;
    std::string nombre;
    std::string apellido;
};

struct Curso
{
    std::string codigo;
    std::string nombre;
    double notaMinimaAprobacion;
};

struct RegistroNota
{
    std::string carnetEstudiante;
    std::string codigoCurso;
    double nota;
};

#endif
