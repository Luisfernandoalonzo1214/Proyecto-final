#ifndef ESTUDIANTES_H
#define ESTUDIANTES_H

#include <string>
#include "estructuras.h"

// Convierte un texto a mayusculas y le quita espacios al inicio/final.
// Se usa para comparar carnets/nombres sin importar como los escriba el usuario.
std::string normalizarTexto(const std::string &texto);

// Valida el formato del carnet: ####-##-##### (4 digitos, guion, 2 digitos, guion, 5 digitos).
bool validarFormatoCarnet(const std::string &carnet);

// Busca un estudiante por carnet (comparacion exacta, normalizada). Devuelve el indice o -1 si no existe.
int buscarEstudiantePorCarnet(const Estudiante lista[], int total, const std::string &carnet);

// Busca estudiantes cuyo nombre o apellido contenga el texto dado (busqueda parcial).
// Llena el arreglo 'resultados' con los indices encontrados y devuelve cuantos encontro.
int buscarEstudiantesPorNombre(const Estudiante lista[], int total, const std::string &texto, int resultados[]);

// Registra un nuevo estudiante. Devuelve false si ya existe el carnet o no hay espacio.
bool registrarEstudiante(Estudiante lista[], int &total, int capacidad,
                          const std::string &carnet, const std::string &nombre, const std::string &apellido);

// Edita nombre y apellido de un estudiante ya existente. Devuelve false si no se encontro.
bool editarEstudiante(Estudiante lista[], int total, const std::string &carnet,
                       const std::string &nuevoNombre, const std::string &nuevoApellido);

// Muestra los datos de un solo estudiante por consola.
void mostrarEstudiante(const Estudiante &est);

// Lista todos los estudiantes registrados.
void listarEstudiantes(const Estudiante lista[], int total);

// Cuenta cuantos estudiantes hay de forma RECURSIVA (requisito del proyecto).
// Caso base: total == 0. Caso recursivo: 1 + contarEstudiantesRecursivo(lista, total - 1).
int contarEstudiantesRecursivo(const Estudiante lista[], int total);

// Menu interactivo por consola del modulo Estudiantes. Se llama desde main().
void menuEstudiantes(Estudiante estudiantes[], int &totalEstudiantes, int capacidad);

#endif
