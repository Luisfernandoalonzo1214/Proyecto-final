#include "persistencia.h"
#include "estudiantes.h"
#include "cursos_notas.h"
#include <fstream>
#include <sstream>
#include <string>

// ---------- Auxiliares ----------
// El separador '|' no puede aparecer dentro de un dato; se reemplaza por espacio al guardar.
static std::string limpiarCampo(const std::string &texto)
{
    std::string r = texto;
    for (size_t i = 0; i < r.size(); i++)
        if (r[i] == '|' || r[i] == '\n' || r[i] == '\r') r[i] = ' ';
    return r;
}

// Divide una linea en exactamente 3 campos separados por '|'.
static bool dividirLinea(const std::string &linea, std::string campos[3])
{
    std::istringstream ss(linea);
    for (int i = 0; i < 3; i++)
    {
        if (!std::getline(ss, campos[i], '|')) return false;
    }
    std::string sobrante;
    if (std::getline(ss, sobrante, '|')) return false; // hay mas de 3 campos
    return true;
}

// Convierte texto a double validando que todo el texto sea numero.
static bool convertirDouble(const std::string &texto, double &valor)
{
    std::istringstream ss(texto);
    ss >> valor;
    if (ss.fail()) return false;
    char extra;
    return !(ss >> extra);
}

static void quitarRetorno(std::string &linea)
{
    if (!linea.empty() && linea[linea.size() - 1] == '\r')
        linea.erase(linea.size() - 1);
}

// ---------- Carga ----------
bool inicializarDatos(Estudiante estudiantes[], int &totalEstudiantes,
                      Curso cursos[], int &totalCursos,
                      RegistroNota notas[], int &totalNotas)
{
    totalEstudiantes = 0;
    totalCursos = 0;
    totalNotas = 0;
    bool todoBien = true;
    std::string linea, c[3];

    // --- estudiantes ---
    {
        std::ifstream f(ARCHIVO_ESTUDIANTES);
        if (f.is_open())
        {
            while (std::getline(f, linea))
            {
                quitarRetorno(linea);
                if (linea.empty()) continue;
                if (!dividirLinea(linea, c)) continue;
                registrarEstudiante(estudiantes, totalEstudiantes, MAX_ESTUDIANTES, c[0], c[1], c[2]);
            }
            if (f.bad()) todoBien = false;
        }
    }

    // --- cursos ---
    {
        std::ifstream f(ARCHIVO_CURSOS);
        if (f.is_open())
        {
            while (std::getline(f, linea))
            {
                quitarRetorno(linea);
                if (linea.empty()) continue;
                double minima;
                if (!dividirLinea(linea, c) || !convertirDouble(c[2], minima)) continue;
                registrarCurso(cursos, totalCursos, MAX_CURSOS, c[0], c[1], minima);
            }
            if (f.bad()) todoBien = false;
        }
    }

    // --- notas (solo si existen el estudiante y el curso) ---
    {
        std::ifstream f(ARCHIVO_NOTAS);
        if (f.is_open())
        {
            while (std::getline(f, linea))
            {
                quitarRetorno(linea);
                if (linea.empty()) continue;
                double nota;
                if (!dividirLinea(linea, c) || !convertirDouble(c[2], nota)) continue;
                registrarNota(notas, totalNotas, MAX_NOTAS,
                              estudiantes, totalEstudiantes,
                              cursos, totalCursos, c[0], c[1], nota);
            }
            if (f.bad()) todoBien = false;
        }
    }

    return todoBien;
}

// ---------- Guardado ----------
bool guardarProgreso(const Estudiante estudiantes[], int totalEstudiantes,
                     const Curso cursos[], int totalCursos,
                     const RegistroNota notas[], int totalNotas)
{
    {
        std::ofstream f(ARCHIVO_ESTUDIANTES);
        if (!f.is_open()) return false;
        for (int i = 0; i < totalEstudiantes; i++)
            f << limpiarCampo(estudiantes[i].carnet) << '|'
              << limpiarCampo(estudiantes[i].nombre) << '|'
              << limpiarCampo(estudiantes[i].apellido) << '\n';
        if (!f.good()) return false;
    }
    {
        std::ofstream f(ARCHIVO_CURSOS);
        if (!f.is_open()) return false;
        for (int i = 0; i < totalCursos; i++)
            f << limpiarCampo(cursos[i].codigo) << '|'
              << limpiarCampo(cursos[i].nombre) << '|'
              << cursos[i].notaMinimaAprobacion << '\n';
        if (!f.good()) return false;
    }
    {
        std::ofstream f(ARCHIVO_NOTAS);
        if (!f.is_open()) return false;
        for (int i = 0; i < totalNotas; i++)
            f << limpiarCampo(notas[i].carnetEstudiante) << '|'
              << limpiarCampo(notas[i].codigoCurso) << '|'
              << notas[i].nota << '\n';
        if (!f.good()) return false;
    }
    return true;
}
