#ifndef ASISTENCIA_H
#define ASISTENCIA_H

// Estructura principal
typedef struct {
    int id;
    char nombre[50];
    int asistencia[31]; // Un espacio para cada día del mes (1 al 31)
    int activo;         // 1 = Activo, 0 = Borrado
} Estudiante;

// Prototipos de funciones
void mostrarMenu();
void cargarDatos(Estudiante lista[], int *contador);
void guardarDatos(Estudiante lista[], int contador);
void registrarEstudiante(Estudiante lista[], int *contador);
void pasarAsistenciaDiaria(Estudiante lista[], int contador);
void borrarEstudiante(Estudiante lista[], int contador);
void generarReporteMensual(Estudiante lista[], int contador);

#endif