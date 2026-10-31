#ifndef CURSOS_NOTAS_H
#define CURSOS_NOTAS_H
#include <string>
#include "estructuras.h"
int buscarCursoPorCodigo(const Curso lista[], int total, const std::string &codigo);
bool registrarCurso(Curso lista[], int &total, int capacidad, const std::string &codigo, const std::string &nombre, double notaMinima);
void listarCursos(const Curso lista[], int total);
bool validarRangoNota(double nota);
int buscarNota(const RegistroNota notas[], int totalNotas, const std::string &carnet, const std::string &codigoCurso);
bool registrarNota(RegistroNota notas[], int &totalNotas, int capacidad, const Estudiante estudiantes[], int totalEstudiantes, const Curso cursos[], int totalCursos, const std::string &carnet, const std::string &codigoCurso, double nota);
bool modificarNota(RegistroNota notas[], int totalNotas, const std::string &carnet, const std::string &codigoCurso, double nuevaNota);
void menuCursosNotas(Curso cursos[], int &totalCursos, int capacidadCursos, RegistroNota notas[], int &totalNotas, int capacidadNotas, const Estudiante estudiantes[], int totalEstudiantes);
#endif
