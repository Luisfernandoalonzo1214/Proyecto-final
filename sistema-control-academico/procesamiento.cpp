#include "procesamiento.h"
#include "estudiantes.h" // normalizarTexto

double sumarNotasRecursivo(const RegistroNota notas[], int totalNotas, const std::string &carnet, int indice)
{
    if (indice == totalNotas) return 0.0; // caso base: se recorrieron todos los registros

    double resto = sumarNotasRecursivo(notas, totalNotas, carnet, indice + 1); // caso recursivo

    if (normalizarTexto(notas[indice].carnetEstudiante) == normalizarTexto(carnet))
        return notas[indice].nota + resto;

    return resto;
}

int contarNotasEstudianteRecursivo(const RegistroNota notas[], int totalNotas, const std::string &carnet, int indice)
{
    if (indice == totalNotas) return 0; // caso base

    int resto = contarNotasEstudianteRecursivo(notas, totalNotas, carnet, indice + 1); // caso recursivo

    if (normalizarTexto(notas[indice].carnetEstudiante) == normalizarTexto(carnet))
        return 1 + resto;

    return resto;
}

double calcularPromedioEstudiante(const std::string &carnet, const RegistroNota notas[], int totalNotas)
{
    int cantidad = contarNotasEstudianteRecursivo(notas, totalNotas, carnet, 0);
    if (cantidad == 0) return 0.0;
    double suma = sumarNotasRecursivo(notas, totalNotas, carnet, 0);
    return suma / cantidad;
}

double calcularPromedioEstudianteEnCurso(const std::string &carnet, const std::string &codigoCurso,
                                          const RegistroNota notas[], int totalNotas)
{
    for (int i = 0; i < totalNotas; i++)
    {
        if (normalizarTexto(notas[i].carnetEstudiante) == normalizarTexto(carnet) &&
            normalizarTexto(notas[i].codigoCurso) == normalizarTexto(codigoCurso))
        {
            return notas[i].nota; // una sola nota por estudiante-curso en este diseno
        }
    }
    return 0.0;
}

std::string determinarResultado(double promedio, double notaMinimaAprobacion)
{
    if (promedio >= notaMinimaAprobacion)
        return "APROBADO";
    return "REPROBADO";
}

double calcularPromedioCurso(const std::string &codigoCurso, const RegistroNota notas[], int totalNotas)
{
    double suma = 0;
    int cantidad = 0;
    for (int i = 0; i < totalNotas; i++)
    {
        if (normalizarTexto(notas[i].codigoCurso) == normalizarTexto(codigoCurso))
        {
            suma += notas[i].nota;
            cantidad++;
        }
    }
    if (cantidad == 0) return 0.0;
    return suma / cantidad;
}

double calcularUmbralEstudiante(const std::string &carnet, const RegistroNota notas[], int totalNotas,
                                 const Curso cursos[], int totalCursos)
{
    double suma = 0;
    int cantidad = 0;
    for (int i = 0; i < totalNotas; i++)
    {
        if (normalizarTexto(notas[i].carnetEstudiante) != normalizarTexto(carnet)) continue;
        for (int j = 0; j < totalCursos; j++)
        {
            if (normalizarTexto(cursos[j].codigo) == normalizarTexto(notas[i].codigoCurso))
            {
                suma += cursos[j].notaMinimaAprobacion;
                cantidad++;
                break;
            }
        }
    }
    if (cantidad == 0) return 0.0;
    return suma / cantidad;
}

int contarEstudiantesConNotasRecursivo(const Estudiante estudiantes[], int totalEstudiantes,
                                        const RegistroNota notas[], int totalNotas, int indice)
{
    if (indice == totalEstudiantes) return 0; // caso base

    int resto = contarEstudiantesConNotasRecursivo(estudiantes, totalEstudiantes, notas, totalNotas, indice + 1);

    if (contarNotasEstudianteRecursivo(notas, totalNotas, estudiantes[indice].carnet, 0) > 0)
        return 1 + resto;
    return resto;
}

int contarAprobadosRecursivo(const Estudiante estudiantes[], int totalEstudiantes,
                              const RegistroNota notas[], int totalNotas,
                              const Curso cursos[], int totalCursos, int indice)
{
    if (indice == totalEstudiantes) return 0; // caso base

    int resto = contarAprobadosRecursivo(estudiantes, totalEstudiantes, notas, totalNotas,
                                          cursos, totalCursos, indice + 1); // caso recursivo

    const std::string &carnet = estudiantes[indice].carnet;
    if (contarNotasEstudianteRecursivo(notas, totalNotas, carnet, 0) == 0)
        return resto; // sin notas: no cuenta ni como aprobado ni como reprobado

    double promedio = calcularPromedioEstudiante(carnet, notas, totalNotas);
    double umbral = calcularUmbralEstudiante(carnet, notas, totalNotas, cursos, totalCursos);

    if (determinarResultado(promedio, umbral) == "APROBADO")
        return 1 + resto;
    return resto;
}

double calcularPromedioGeneral(const Estudiante estudiantes[], int totalEstudiantes,
                                const RegistroNota notas[], int totalNotas)
{
    double suma = 0;
    int conNotas = 0;
    for (int i = 0; i < totalEstudiantes; i++)
    {
        if (contarNotasEstudianteRecursivo(notas, totalNotas, estudiantes[i].carnet, 0) == 0) continue;
        suma += calcularPromedioEstudiante(estudiantes[i].carnet, notas, totalNotas);
        conNotas++;
    }
    if (conNotas == 0) return 0.0;
    return suma / conNotas; // los estudiantes sin notas no entran al promedio
}

void construirMatrizCalificaciones(const Estudiante estudiantes[], int totalEstudiantes,
                                    const Curso cursos[], int totalCursos,
                                    const RegistroNota notas[], int totalNotas,
                                    double matriz[][MAX_CURSOS])
{
    for (int i = 0; i < totalEstudiantes; i++)
    {
        for (int j = 0; j < totalCursos; j++)
        {
            matriz[i][j] = calcularPromedioEstudianteEnCurso(estudiantes[i].carnet, cursos[j].codigo, notas, totalNotas);
        }
    }
}

int indiceEstudianteConMayorPromedio(const Estudiante estudiantes[], int totalEstudiantes,
                                      const RegistroNota notas[], int totalNotas)
{
    int mejorIndice = -1;
    double mejorPromedio = 0;

    for (int i = 0; i < totalEstudiantes; i++)
    {
        if (contarNotasEstudianteRecursivo(notas, totalNotas, estudiantes[i].carnet, 0) == 0) continue;
        double promedio = calcularPromedioEstudiante(estudiantes[i].carnet, notas, totalNotas);
        if (mejorIndice == -1 || promedio > mejorPromedio)
        {
            mejorPromedio = promedio;
            mejorIndice = i;
        }
    }
    return mejorIndice; // -1 si ningun estudiante tiene notas
}
