#include <iostream>
#include <sstream>
#include <string>
#include "estructuras.h"
#include "estudiantes.h"
#include "cursos_notas.h"
#include "reportes.h"
#include "persistencia.h"

using namespace std;

static int leerOpcionPrincipal()
{
    string linea;
    if (!getline(cin, linea)) return 0;
    istringstream ss(linea);
    int v;
    char extra;
    if (!(ss >> v) || (ss >> extra)) return -1;
    return v;
}

int main() {
    static Estudiante estudiantes[MAX_ESTUDIANTES];
    static Curso cursos[MAX_CURSOS];
    static RegistroNota notas[MAX_NOTAS];
    int totalEstudiantes = 0, totalCursos = 0, totalNotas = 0;

    // Carga los datos guardados (estudiantes.txt, cursos.txt, notas.txt)
    inicializarDatos(estudiantes, totalEstudiantes,
                     cursos, totalCursos,
                     notas, totalNotas);

    int opcionPrincipal = -1;
    do {
        cout << "\n========================================\n";
        cout << "   SISTEMA DE CONTROL ACADEMICO - UMG   \n";
        cout << "========================================\n";
        cout << "1. Modulo de Estudiantes\n";
        cout << "2. Modulo de Cursos y Notas\n";
        cout << "3. Modulo de Reportes y Consultas\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        opcionPrincipal = leerOpcionPrincipal();

        switch (opcionPrincipal) {
            case 1:
                menuEstudiantes(estudiantes, totalEstudiantes, MAX_ESTUDIANTES);
                guardarProgreso(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
                break;
            case 2:
                menuCursosNotas(cursos, totalCursos, MAX_CURSOS,
                                notas, totalNotas, MAX_NOTAS,
                                estudiantes, totalEstudiantes);
                guardarProgreso(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
                break;
            case 3:
                menuReportes(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
                break;
            case 0:
                if (guardarProgreso(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas))
                    cout << "Progreso guardado. Saliendo del sistema...\n";
                else
                    cout << "Error al guardar el progreso.\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcionPrincipal != 0);

    return 0;
}
