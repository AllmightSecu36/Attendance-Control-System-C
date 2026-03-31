#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definimos una estructura que sirver para guardar toda la estructura dentro de el Estudiante
typedef struct {
    int id;
    char nombre[50];
    int presente; // 1 para sí, 0 para no, este booleano es para las asistencias para mas adelante
} Estudiante;

void mostrarMenu() {
    printf("\n--- SISTEMA DE CONTROL DE ASISTENCIA ---\n");
    printf("1. Registrar nuevo estudiante\n");
    printf("2. Marcar asistencia\n");
    printf("3. Generar reporte (.txt)\n");
    printf("4. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int opcion;
    
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("Proximamente: Registro...\n");
                break;
            case 2:
                printf("Proximamente: Asistencia...\n");
                break;
            case 3:
                printf("Proximamente: Reporte...\n");
                break;
            case 4:
                printf("Saliendo del sistema. ¡Buen dia!\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 4);

    return 0;
}