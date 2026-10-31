// Pruebas automaticas del Sistema de Control Academico.
// Compilar con la tarea "Compilar pruebas" y ejecutar pruebas.exe.
#include <cstdio>
#include <iostream>
#include <string>
#include "estructuras.h"
#include "estudiantes.h"
#include "cursos_notas.h"
#include "procesamiento.h"
#include "persistencia.h"

static int total = 0, fallos = 0;

static void verificar(bool condicion, const std::string &descripcion)
{
    total++;
    if (condicion) std::cout << "[OK]    " << descripcion << "\n";
    else { fallos++; std::cout << "[FALLA] " << descripcion << "\n"; }
}

static bool casiIgual(double a, double b) { return (a - b) < 0.0001 && (b - a) < 0.0001; }

int main()
{
    static Estudiante est[MAX_ESTUDIANTES];
    static Curso cur[MAX_CURSOS];
    static RegistroNota notas[MAX_NOTAS];
    int nEst = 0, nCur = 0, nNot = 0;

    std::cout << "=== MODULO 1: ESTUDIANTES ===\n";
    verificar(validarFormatoCarnet("6590-26-16521"), "Carnet con formato valido");
    verificar(!validarFormatoCarnet("6590-26"), "Carnet incompleto se rechaza");
    verificar(!validarFormatoCarnet("ABCD-26-16521"), "Carnet con letras se rechaza");
    verificar(!validarFormatoCarnet("6590--16521"), "Carnet con grupo vacio se rechaza");
    verificar(registrarEstudiante(est, nEst, MAX_ESTUDIANTES, "6590-26-16521", "Luis", "Alonzo"), "Registrar estudiante 1");
    verificar(registrarEstudiante(est, nEst, MAX_ESTUDIANTES, " 6590-26-00002 ", "Maria", "Lopez"), "Registrar estudiante 2 (con espacios)");
    verificar(!registrarEstudiante(est, nEst, MAX_ESTUDIANTES, "6590-26-16521", "Otro", "Repetido"), "Carnet duplicado se rechaza");
    verificar(!registrarEstudiante(est, nEst, MAX_ESTUDIANTES, "6590-26-00003", "", "Vacio"), "Nombre vacio se rechaza");
    verificar(nEst == 2, "Hay 2 estudiantes");
    verificar(contarEstudiantesRecursivo(est, nEst) == 2, "Conteo recursivo de estudiantes = 2");
    verificar(buscarEstudiantePorCarnet(est, nEst, "6590-26-00002") == 1, "Busqueda por carnet (normalizada)");
    verificar(buscarEstudiantePorCarnet(est, nEst, "0000-00-00000") == -1, "Carnet inexistente devuelve -1");
    int res[MAX_ESTUDIANTES];
    verificar(buscarEstudiantesPorNombre(est, nEst, "alon", res) == 1 && res[0] == 0, "Busqueda parcial por nombre/apellido");
    verificar(buscarEstudiantesPorNombre(est, nEst, "", res) == 0, "Busqueda vacia no devuelve todo");
    verificar(editarEstudiante(est, nEst, "6590-26-00002", "Maria", "Lopez Perez") && est[1].apellido == "Lopez Perez", "Editar estudiante");
    verificar(!editarEstudiante(est, nEst, "9999-99-99999", "X", "Y"), "Editar estudiante inexistente falla");

    std::cout << "\n=== MODULO 2: CURSOS Y NOTAS ===\n";
    verificar(registrarCurso(cur, nCur, MAX_CURSOS, "alg101", "Algoritmos", 61), "Registrar curso ALG101 (minima 61)");
    verificar(registrarCurso(cur, nCur, MAX_CURSOS, "MAT101", "Matematica", 70), "Registrar curso MAT101 (minima 70)");
    verificar(!registrarCurso(cur, nCur, MAX_CURSOS, "ALG101", "Repetido", 61), "Codigo de curso duplicado se rechaza");
    verificar(!registrarCurso(cur, nCur, MAX_CURSOS, "AL G", "Con espacio", 61), "Codigo de curso con espacio se rechaza");
    verificar(!registrarCurso(cur, nCur, MAX_CURSOS, "FIS101", "Fisica", 150), "Nota minima fuera de rango se rechaza");
    verificar(buscarCursoPorCodigo(cur, nCur, " Mat101 ") == 1, "Busqueda de curso normalizada");

    verificar(registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-16521", "ALG101", 85), "Registrar nota 85");
    verificar(!registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-16521", "ALG101", 90), "Nota repetida estudiante-curso se rechaza");
    verificar(!registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-16521", "MAT101", 101), "Nota 101 (fuera de rango) se rechaza");
    verificar(!registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-16521", "MAT101", -1), "Nota -1 (fuera de rango) se rechaza");
    verificar(!registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "9999-99-99999", "ALG101", 80), "Nota para estudiante inexistente se rechaza");
    verificar(!registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-16521", "XXX999", 80), "Nota para curso inexistente se rechaza");
    verificar(registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-16521", "MAT101", 60), "Registrar nota 60 en MAT101");
    verificar(registrarNota(notas, nNot, MAX_NOTAS, est, nEst, cur, nCur, "6590-26-00002", "ALG101", 50), "Registrar nota 50 al estudiante 2");
    verificar(nNot == 3, "Hay 3 notas registradas");
    verificar(modificarNota(notas, nNot, "6590-26-00002", "ALG101", 75), "Modificar nota existente");
    verificar(!modificarNota(notas, nNot, "6590-26-00002", "ALG101", 200), "Modificar con valor fuera de rango falla");
    verificar(!modificarNota(notas, nNot, "6590-26-00002", "MAT101", 80), "Modificar nota inexistente falla");

    std::cout << "\n=== MODULO 4: PROCESAMIENTO ===\n";
    verificar(casiIgual(calcularPromedioEstudiante("6590-26-16521", notas, nNot), 72.5), "Promedio estudiante 1 = 72.5");
    verificar(casiIgual(calcularPromedioEstudiante("6590-26-00002", notas, nNot), 75.0), "Promedio estudiante 2 = 75 (nota modificada)");
    verificar(casiIgual(calcularPromedioCurso("ALG101", notas, nNot), 80.0), "Promedio curso ALG101 = 80");
    verificar(casiIgual(calcularPromedioCurso("MAT101", notas, nNot), 60.0), "Promedio curso MAT101 = 60");
    verificar(casiIgual(calcularUmbralEstudiante("6590-26-16521", notas, nNot, cur, nCur), 65.5), "Umbral estudiante 1 = (61+70)/2 = 65.5");
    verificar(determinarResultado(72.5, 65.5) == "APROBADO", "72.5 contra 65.5 = APROBADO");
    verificar(determinarResultado(60, 61) == "REPROBADO", "60 contra 61 = REPROBADO");
    verificar(contarEstudiantesConNotasRecursivo(est, nEst, notas, nNot, 0) == 2, "2 estudiantes con notas");
    verificar(contarAprobadosRecursivo(est, nEst, notas, nNot, cur, nCur, 0) == 2, "2 aprobados (recursivo)");
    verificar(casiIgual(calcularPromedioGeneral(est, nEst, notas, nNot), 73.75), "Promedio general = 73.75");
    verificar(indiceEstudianteConMayorPromedio(est, nEst, notas, nNot) == 1, "Mayor promedio = estudiante 2");

    // Los promedios deben actualizarse con los datos, no quedar fijos
    modificarNota(notas, nNot, "6590-26-00002", "ALG101", 40);
    verificar(casiIgual(calcularPromedioEstudiante("6590-26-00002", notas, nNot), 40.0), "Promedio se actualiza al cambiar la nota");
    verificar(contarAprobadosRecursivo(est, nEst, notas, nNot, cur, nCur, 0) == 1, "Aprobados se actualiza (ahora 1)");
    verificar(indiceEstudianteConMayorPromedio(est, nEst, notas, nNot) == 0, "Mayor promedio se actualiza (estudiante 1)");

    // Estudiante sin notas no cuenta como reprobado ni afecta el promedio general
    registrarEstudiante(est, nEst, MAX_ESTUDIANTES, "6590-26-00003", "Sin", "Notas");
    verificar(contarEstudiantesConNotasRecursivo(est, nEst, notas, nNot, 0) == 2, "Estudiante sin notas no se cuenta");
    verificar(casiIgual(calcularPromedioGeneral(est, nEst, notas, nNot), 56.25), "Promedio general ignora estudiantes sin notas");

    double matriz[MAX_ESTUDIANTES][MAX_CURSOS];
    construirMatrizCalificaciones(est, nEst, cur, nCur, notas, nNot, matriz);
    verificar(casiIgual(matriz[0][0], 85) && casiIgual(matriz[0][1], 60) && casiIgual(matriz[1][0], 40) && casiIgual(matriz[1][1], 0),
              "Matriz estudiante x curso correcta");

    std::cout << "\n=== MODULO 5: PERSISTENCIA ===\n";
    verificar(guardarProgreso(est, nEst, cur, nCur, notas, nNot), "Guardar progreso");
    static Estudiante est2[MAX_ESTUDIANTES];
    static Curso cur2[MAX_CURSOS];
    static RegistroNota notas2[MAX_NOTAS];
    int nEst2 = 0, nCur2 = 0, nNot2 = 0;
    verificar(inicializarDatos(est2, nEst2, cur2, nCur2, notas2, nNot2), "Cargar progreso");
    verificar(nEst2 == nEst && nCur2 == nCur && nNot2 == nNot, "Cantidades iguales tras cargar (3, 2, 3)");
    verificar(est2[1].apellido == "Lopez Perez" && cur2[1].codigo == "MAT101" && casiIgual(notas2[2].nota, 40),
              "Datos iguales tras guardar y cargar");

    std::remove(ARCHIVO_ESTUDIANTES);
    std::remove(ARCHIVO_CURSOS);
    std::remove(ARCHIVO_NOTAS);
    nEst2 = 7; nCur2 = 7; nNot2 = 7;
    verificar(inicializarDatos(est2, nEst2, cur2, nCur2, notas2, nNot2) && nEst2 == 0 && nCur2 == 0 && nNot2 == 0,
              "Sin archivos: arranca vacio sin error");

    std::cout << "\nResultado: " << (total - fallos) << " de " << total << " pruebas correctas.\n";
    return fallos == 0 ? 0 : 1;
}
