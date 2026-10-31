#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "reportes.h"
#include "estructuras.h"
#include "estudiantes.h"
#include "procesamiento.h"

using namespace std;

// 1. Encabezado del sistema
void mostrarEncabezado() {
    cout << "\n==================================================\n";
    cout << "             REPORTE ACADEMICO                    \n";
    cout << "     Sistema de Control de Notas - UMG            \n";
    cout << "==================================================\n";
}

// 2. Reporte individual de un estudiante
void mostrarReporteEstudiante(string nombreCompleto, double promedio, string resultado) {
    cout << "--------------------------------------------------\n";
    cout << " Estudiante: " << nombreCompleto << "\n";
    cout << " Promedio:   " << fixed << setprecision(2) << promedio << "\n";
    cout << " Resultado:  " << resultado << "\n";
    cout << "--------------------------------------------------\n";
}

// 3. Reporte general del grupo
void mostrarReporteGeneral(int total, int aprobados, int reprobados, double promedioGeneral) {
    cout << "\n==================================================\n";
    cout << "             RESUMEN GENERAL                      \n";
    cout << "==================================================\n";
    cout << " Total estudiantes : " << total << "\n";
    cout << " Aprobados         : " << aprobados << "\n";
    cout << " Reprobados        : " << reprobados << "\n";
    cout << " Promedio general  : " << fixed << setprecision(2) << promedioGeneral << "\n";
    cout << "==================================================\n\n";
}

// 4. Función extra (Cadenas y Búsquedas)
// Muestra el expediente completo de un estudiante buscándolo por su nombre o carnet.
void mostrarExpedienteEstudiante(const Estudiante estudiantes[], int totalEst, 
                                  const RegistroNota notas[], int totalNotas,
                                  const Curso cursos[], int totalCursos, 
                                  string busqueda) {
    bool encontrado = false;
    string buscado = normalizarTexto(busqueda);
    if (buscado.empty()) {
        cout << "\n[!] Debe escribir un carnet o un nombre.\n";
        return;
    }
    
    for (int i = 0; i < totalEst; i++) {
        string nombreCompleto = estudiantes[i].nombre + " " + estudiantes[i].apellido;
        
        // Búsqueda por carnet exacto o por nombre parcial (usando find), sin importar mayusculas
        if (normalizarTexto(estudiantes[i].carnet) == buscado ||
            normalizarTexto(nombreCompleto).find(buscado) != string::npos) {
            encontrado = true;
            cout << "\n==================================================\n";
            cout << " EXPEDIENTE DEL ESTUDIANTE                        \n";
            cout << "==================================================\n";
            cout << " Nombre: " << nombreCompleto << "\n";
            cout << " Carnet: " << estudiantes[i].carnet << "\n";
            cout << "--------------------------------------------------\n";
            cout << " Cursos y Notas:\n";
            
            for (int j = 0; j < totalNotas; j++) {
                if (normalizarTexto(notas[j].carnetEstudiante) == normalizarTexto(estudiantes[i].carnet)) {
                    string nombreCurso = notas[j].codigoCurso;
                    // Buscar el nombre real del curso
                    for (int k = 0; k < totalCursos; k++) {
                        if (normalizarTexto(cursos[k].codigo) == normalizarTexto(notas[j].codigoCurso)) {
                            nombreCurso = cursos[k].nombre;
                            break;
                        }
                    }
                    cout << "   - " << left << setw(20) << nombreCurso 
                         << " | Nota: " << notas[j].nota << "\n";
                }
            }
            if (contarNotasEstudianteRecursivo(notas, totalNotas, estudiantes[i].carnet, 0) == 0) {
                cout << "   (sin notas registradas)\n";
            } else {
                double promedio = calcularPromedioEstudiante(estudiantes[i].carnet, notas, totalNotas);
                double umbral = calcularUmbralEstudiante(estudiantes[i].carnet, notas, totalNotas, cursos, totalCursos);
                cout << "--------------------------------------------------\n";
                cout << " Promedio: " << fixed << setprecision(2) << promedio
                     << " | Resultado: " << determinarResultado(promedio, umbral) << "\n";
            }
            cout << "==================================================\n";
        }
    }
    
    if (!encontrado) {
        cout << "\n[!] No se encontro ningun estudiante con: " << busqueda << "\n";
    }
}

// ---------- Menu del modulo ----------

// Lee una linea y la convierte a entero. Devuelve -1 si no es un numero y 0 si se acabo la entrada.
static int leerOpcion() {
    string linea;
    if (!getline(cin, linea)) return 0;
    istringstream ss(linea);
    int valor;
    char extra;
    if (!(ss >> valor) || (ss >> extra)) return -1;
    return valor;
}

static void reportePromedioEstudiante(const Estudiante estudiantes[], int totalEstudiantes,
                                      const Curso cursos[], int totalCursos,
                                      const RegistroNota notas[], int totalNotas) {
    string carnet;
    cout << "Carnet del estudiante: ";
    getline(cin, carnet);
    int idx = buscarEstudiantePorCarnet(estudiantes, totalEstudiantes, carnet);
    if (idx == -1) {
        cout << "No se encontro ese estudiante.\n";
        return;
    }
    if (contarNotasEstudianteRecursivo(notas, totalNotas, estudiantes[idx].carnet, 0) == 0) {
        cout << "El estudiante no tiene notas registradas.\n";
        return;
    }
    double promedio = calcularPromedioEstudiante(estudiantes[idx].carnet, notas, totalNotas);
    double umbral = calcularUmbralEstudiante(estudiantes[idx].carnet, notas, totalNotas, cursos, totalCursos);
    mostrarReporteEstudiante(estudiantes[idx].nombre + " " + estudiantes[idx].apellido,
                             promedio, determinarResultado(promedio, umbral));
}

static void reportePromedioCurso(const Curso cursos[], int totalCursos,
                                 const RegistroNota notas[], int totalNotas) {
    if (totalCursos == 0) {
        cout << "No hay cursos registrados.\n";
        return;
    }
    cout << "\n--- PROMEDIO POR CURSO ---\n";
    for (int i = 0; i < totalCursos; i++) {
        bool tieneNotas = false;
        for (int j = 0; j < totalNotas && !tieneNotas; j++)
            if (normalizarTexto(notas[j].codigoCurso) == normalizarTexto(cursos[i].codigo)) tieneNotas = true;

        cout << " " << cursos[i].codigo << " - " << left << setw(20) << cursos[i].nombre << " : ";
        if (tieneNotas)
            cout << fixed << setprecision(2) << calcularPromedioCurso(cursos[i].codigo, notas, totalNotas) << "\n";
        else
            cout << "sin notas\n";
    }
}

static void reporteAprobados(const Estudiante estudiantes[], int totalEstudiantes,
                             const Curso cursos[], int totalCursos,
                             const RegistroNota notas[], int totalNotas) {
    int conNotas = contarEstudiantesConNotasRecursivo(estudiantes, totalEstudiantes, notas, totalNotas, 0);
    if (conNotas == 0) {
        cout << "Todavia no hay estudiantes con notas.\n";
        return;
    }
    int aprobados = contarAprobadosRecursivo(estudiantes, totalEstudiantes, notas, totalNotas, cursos, totalCursos, 0);
    mostrarReporteGeneral(conNotas, aprobados, conNotas - aprobados,
                          calcularPromedioGeneral(estudiantes, totalEstudiantes, notas, totalNotas));
}

static void reporteMejorPromedio(const Estudiante estudiantes[], int totalEstudiantes,
                                 const Curso cursos[], int totalCursos,
                                 const RegistroNota notas[], int totalNotas) {
    int idx = indiceEstudianteConMayorPromedio(estudiantes, totalEstudiantes, notas, totalNotas);
    if (idx == -1) {
        cout << "Todavia no hay datos para calcular el mejor promedio.\n";
        return;
    }
    double promedio = calcularPromedioEstudiante(estudiantes[idx].carnet, notas, totalNotas);
    double umbral = calcularUmbralEstudiante(estudiantes[idx].carnet, notas, totalNotas, cursos, totalCursos);
    cout << "\nEstudiante con mayor promedio:";
    mostrarReporteEstudiante(estudiantes[idx].nombre + " " + estudiantes[idx].apellido,
                             promedio, determinarResultado(promedio, umbral));
}

static void reporteMatriz(const Estudiante estudiantes[], int totalEstudiantes,
                          const Curso cursos[], int totalCursos,
                          const RegistroNota notas[], int totalNotas) {
    if (totalEstudiantes == 0 || totalCursos == 0) {
        cout << "Se necesitan estudiantes y cursos para mostrar la matriz.\n";
        return;
    }
    static double matriz[MAX_ESTUDIANTES][MAX_CURSOS];
    construirMatrizCalificaciones(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas, matriz);

    cout << "\n--- MATRIZ DE CALIFICACIONES (estudiante x curso) ---\n";
    cout << left << setw(16) << "Carnet";
    for (int j = 0; j < totalCursos; j++) cout << right << setw(9) << cursos[j].codigo;
    cout << "\n";
    for (int i = 0; i < totalEstudiantes; i++) {
        cout << left << setw(16) << estudiantes[i].carnet;
        for (int j = 0; j < totalCursos; j++)
            cout << right << setw(9) << fixed << setprecision(1) << matriz[i][j];
        cout << "\n";
    }
    cout << "(0.0 = el estudiante no tiene nota en ese curso)\n";
}

void menuReportes(const Estudiante estudiantes[], int totalEstudiantes,
                  const Curso cursos[], int totalCursos,
                  const RegistroNota notas[], int totalNotas) {
    int opcion = -1;
    do {
        cout << "\n--- MODULO REPORTES Y CONSULTAS ---\n";
        cout << "1. Expediente de un estudiante (por carnet o nombre)\n";
        cout << "2. Promedio por estudiante\n";
        cout << "3. Promedio por curso\n";
        cout << "4. Cantidad de aprobados y reprobados\n";
        cout << "5. Estudiante con mayor promedio\n";
        cout << "6. Matriz de calificaciones\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        opcion = leerOpcion();

        if (opcion == 1) {
            string busqueda;
            cout << "Carnet o nombre a buscar: ";
            getline(cin, busqueda);
            mostrarExpedienteEstudiante(estudiantes, totalEstudiantes, notas, totalNotas, cursos, totalCursos, busqueda);
        } else if (opcion == 2) {
            reportePromedioEstudiante(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
        } else if (opcion == 3) {
            reportePromedioCurso(cursos, totalCursos, notas, totalNotas);
        } else if (opcion == 4) {
            reporteAprobados(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
        } else if (opcion == 5) {
            reporteMejorPromedio(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
        } else if (opcion == 6) {
            reporteMatriz(estudiantes, totalEstudiantes, cursos, totalCursos, notas, totalNotas);
        } else if (opcion != 0) {
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);
}
