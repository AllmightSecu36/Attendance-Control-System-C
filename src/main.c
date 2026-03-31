#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Definimos una estructura que sirver para guardar toda la estructura dentro de el Estudiante
//ESTA SERA LA ETIQUETA DONDE SE REGISTRARAN LOS ESTUDIANTES
typedef struct { 
    int id;
    char nombre[50];
    int presente; 
} Estudiante;

void mostrarMenu() {
    printf("\n--- SISTEMA DE CONTROL DE ASISTENCIA ---\n");
    printf("1. Registrar nuevo estudiante\n");
    printf("2. Marcar asistencia\n");
    printf("\n--- SISTEMA DE ASISTENCIA ---");
    printf("\n1. Registrar nuevo estudiante");
    printf("\n2. Marcar asistencia");
    printf("\n3. Generar reporte (.txt)");
    printf("\n4. Salir");
    printf("\nSeleccione una opcion: ");
}
//AQUI SE REGISTRAN LOS ESTUDIANTES
void registrarEstudiante(Estudiante lista[], int *contador) {
    if (*contador >= 100) {
        printf("\n[!] Error: Lista llena.\n");
        return;
    }

    printf("\n--- Registro de Estudiante ---\n");
    
    printf("Ingrese ID (Solo numeros): ");
    scanf("%d", &lista[*contador].id);

    // Mientras el buffer tenga algo (como el Enter), lo sacamos uno por uno.
    while (getchar() != '\n'); 

    printf("Ingrese Nombre Completo: ");
    
    fgets(lista[*contador].nombre, 50, stdin);
    
    
    lista[*contador].nombre[strcspn(lista[*contador].nombre, "\n")] = 0;

    lista[*contador].presente = 0; 
    (*contador)++; 
    
    printf("\n[+] Estudiante registrado con exito.\n");
}

//AQUI ES DONDE COMIENZA EL CORAZON DEL PROGRAMA, AQUI ESTAN LAS OPCIONES
int main() {
    Estudiante lista[100];
    int opcion;

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("\n[!] Use solo numeros.\n");
            continue;
        }

        switch(opcion) {
            case 1:
                registrarEstudiante(lista, &totalAlumnos);
                break;
            case 2:
                break;
                printf("\nProximamente: Marcar asistencia...\n");
                break;
            case 4:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\n[!] Opcion invalida.\n");
        }
    } while (opcion != 4);

    return 0;
}