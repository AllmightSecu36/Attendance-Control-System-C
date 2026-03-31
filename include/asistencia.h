#ifndef ASISTENCIA_H
#define ASISTENCIA_H

//Instrucciones para que no falle nada:
//Asegúrate de que la carpeta data esté creada y vacía.
//Compila desde la carpeta src: gcc main.c -o ../bin/asistencia
//Ejecuta desde la carpeta src: ../bin/asistencia
//Si haces esto, el programa encontrará la carpeta data/ subiendo un nivel (../) y creará los archivos sin chillar.

// Nueva mini-estructura: Guarda la fecha y el estado de ese día
typedef struct {
    char fecha[15]; // Guardará textos como "02/05/2026"
    int presente;   // 1 = Presente, 0 = Falta
} RegistroDiario;

// Estructura principal actualizada
typedef struct {
    int id;
    char nombre[50];
    RegistroDiario historial[100]; // Capacidad para 100 clases en el semestre
    int totalClases;               // Cuántas clases ha tenido este alumno
    int activo;
} Estudiante;

// Prototipos
void mostrarMenu();
void cargarDatos(Estudiante lista[], int *contador);
void guardarDatos(Estudiante lista[], int contador);
void registrarEstudiante(Estudiante lista[], int *contador);
void pasarAsistenciaDiaria(Estudiante lista[], int contador);
void borrarEstudiante(Estudiante lista[], int contador);
void generarReporteMensual(Estudiante lista[], int contador);

#endif