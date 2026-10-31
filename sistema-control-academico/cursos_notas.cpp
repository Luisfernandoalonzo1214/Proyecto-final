#include "cursos_notas.h"
#include "estudiantes.h"
#include "cursos_notas.h"
#include "estudiantes.h" // normalizarTexto
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Lee una linea y la convierte a numero. Devuelve false si no es un numero valido.
static bool leerNumero(double &valor)
{
    std::string linea;
    if (!std::getline(std::cin, linea)) return false;
    std::istringstream ss(linea);
    char extra;
    return (ss >> valor) && !(ss >> extra);
}

int buscarCursoPorCodigo(const Curso lista[], int total, const std::string &codigo)
{
    std::string objetivo = normalizarTexto(codigo);
    for (int i = 0; i < total; i++)
    {
        if (normalizarTexto(lista[i].codigo) == objetivo)
            return i;
    }
    return -1;
}

bool registrarCurso(Curso lista[], int &total, int capacidad,
                     const std::string &codigo, const std::string &nombre, double notaMinima)
{
    if (total >= capacidad) return false;
    std::string codigoLimpio = normalizarTexto(codigo);
    if (codigoLimpio.empty() || nombre.empty()) return false;
    if (codigoLimpio.find(' ') != std::string::npos) return false; // el codigo no lleva espacios
    if (notaMinima < 0 || notaMinima > 100) return false;
    if (buscarCursoPorCodigo(lista, total, codigoLimpio) != -1) return false; // codigo duplicado

    lista[total].codigo = codigoLimpio;
    lista[total].nombre = nombre;
    lista[total].notaMinimaAprobacion = notaMinima;
    total++;
    return true;
}

void listarCursos(const Curso lista[], int total)
{
    if (total == 0)
    {
        std::cout << "No hay ningun curso registrado.\n";
        return;
    }
    for (int i = 0; i < total; i++)
    {
        std::cout << "Codigo: " << lista[i].codigo
                   << " | Nombre: " << lista[i].nombre
                   << " | Nota minima: " << lista[i].notaMinimaAprobacion << std::endl;
    }
}

bool validarRangoNota(double nota)
{
    return nota >= 0 && nota <= 100;
}

int buscarNota(const RegistroNota notas[], int totalNotas, const std::string &carnet, const std::string &codigoCurso)
{
    std::string carnetObjetivo = normalizarTexto(carnet);
    std::string cursoObjetivo = normalizarTexto(codigoCurso);
    for (int i = 0; i < totalNotas; i++)
    {
        if (normalizarTexto(notas[i].carnetEstudiante) == carnetObjetivo &&
            normalizarTexto(notas[i].codigoCurso) == cursoObjetivo)
            return i;
    }
    return -1;
}

bool registrarNota(RegistroNota notas[], int &totalNotas, int capacidad,
                    const Estudiante estudiantes[], int totalEstudiantes,
                    const Curso cursos[], int totalCursos,
                    const std::string &carnet, const std::string &codigoCurso, double nota)
{
    if (totalNotas >= capacidad) return false;
    if (!validarRangoNota(nota)) return false;
    if (buscarEstudiantePorCarnet(estudiantes, totalEstudiantes, carnet) == -1) return false; // no existe el estudiante
    if (buscarCursoPorCodigo(cursos, totalCursos, codigoCurso) == -1) return false; // no existe el curso
    if (buscarNota(notas, totalNotas, carnet, codigoCurso) != -1) return false; // ya existe, usar modificarNota

    notas[totalNotas].carnetEstudiante = normalizarTexto(carnet);
    notas[totalNotas].codigoCurso = normalizarTexto(codigoCurso);
    notas[totalNotas].nota = nota;
    totalNotas++;
    return true;
}

bool modificarNota(RegistroNota notas[], int totalNotas,
                    const std::string &carnet, const std::string &codigoCurso, double nuevaNota)
{
    if (!validarRangoNota(nuevaNota)) return false;
    int idx = buscarNota(notas, totalNotas, carnet, codigoCurso);
    if (idx == -1) return false;
    notas[idx].nota = nuevaNota;
    return true;
}

void menuCursosNotas(Curso cursos[], int &totalCursos, int capacidadCursos,
                      RegistroNota notas[], int &totalNotas, int capacidadNotas,
                      const Estudiante estudiantes[], int totalEstudiantes)
{
    int opcion = -1;
    do
    {
        std::cout << "\n--- MODULO CURSOS Y NOTAS ---\n";
        std::cout << "1. Registrar un curso\n";
        std::cout << "2. Lista de los cursos\n";
        std::cout << "3. Registrar notas\n";
        std::cout << "4. Modificar las notas\n";
        std::cout << "0. Regresar al menu de inicio\n";
        std::cout << "Opcion: ";
        double leida;
        if (!std::cin.good() && std::cin.eof()) break;
        opcion = leerNumero(leida) ? (int)leida : -1;

        if (opcion == 1)
        {
            std::string codigo, nombre;
            double notaMinima;
            std::cout << "Codigo del curso: "; std::getline(std::cin, codigo);
            std::cout << "Nombre del curso: "; std::getline(std::cin, nombre);
            std::cout << "Nota minima de aprobacion (0-100): ";
            if (!leerNumero(notaMinima)) { std::cout << "Debe escribir un numero.\n"; continue; }
            if (registrarCurso(cursos, totalCursos, capacidadCursos, codigo, nombre, notaMinima))
                std::cout << "Curso registrado.\n";
            else
                std::cout << "No se pudo registrar el curso (codigo duplicado, con espacios o datos invalidos).\n";
        }
        else if (opcion == 2)
        {
            listarCursos(cursos, totalCursos);
        }
        else if (opcion == 3)
        {
            std::string carnet, codigo;
            double nota;
            std::cout << "Carnet del estudiante: "; std::getline(std::cin, carnet);
            std::cout << "Codigo del curso: "; std::getline(std::cin, codigo);
            std::cout << "Nota (0-100): ";
            if (!leerNumero(nota)) { std::cout << "Debe escribir un numero.\n"; continue; }
            if (registrarNota(notas, totalNotas, capacidadNotas, estudiantes, totalEstudiantes,
                               cursos, totalCursos, carnet, codigo, nota))
                std::cout << "Nota registrada.\n";
            else
                std::cout << "No se pudo registrar (estudiante/curso inexistente, nota fuera de rango o ya existe).\n";
        }
        else if (opcion == 4)
        {
            std::string carnet, codigo;
            double nota;
            std::cout << "Carnet del estudiante: "; std::getline(std::cin, carnet);
            std::cout << "Codigo del curso: "; std::getline(std::cin, codigo);
            std::cout << "Nueva nota (0-100): ";
            if (!leerNumero(nota)) { std::cout << "Debe escribir un numero.\n"; continue; }
            if (modificarNota(notas, totalNotas, carnet, codigo, nota))
                std::cout << "Nota actualizada.\n";
            else
                std::cout << "No se encontro esa nota o el valor es invalido.\n";
        }
        else if (opcion != 0)
        {
            std::cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}
