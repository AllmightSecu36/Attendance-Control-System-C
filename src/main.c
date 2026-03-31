#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//ESTA SERA LA ETIQUETA DONDE SE REGISTRARAN LOS ESTUDIANTES
typedef struct { 
    int id;
    char nombre[50];
    int presente; 
} Estudiante;

//ESTA FUNCION MOSTRARA LAS OPCIONES

void mostrarMenu() {
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

//AQUI SE REGISTRAN LAS ASISITENCIAS

void marcarAsistencia(Estudiante lista[], int contador) {
    int idBuscar;
    int encontrado = 0;

    if (contador == 0) {
        printf("\n[!] No hay estudiantes registrados aun.\n");
        return;
    }

    printf("\n--- Marcar Asistencia ---");
    printf("\nIngrese el ID del estudiante: ");
    scanf("%d", &idBuscar);

    for (int i = 0; i < contador; i++) {
        if (lista[i].id == idBuscar) {
            lista[i].presente = 1;
            encontrado = 1;
            printf("\n[OK] Asistencia marcada para: %s\n", lista[i].nombre);
            break;
        }
    }

    if (!encontrado) {
        printf("\n[!] Estudiante con ID %d no encontrado.\n", idBuscar);
    }
}

//AQUI ES DONDE COMIENZA EL CORAZON DEL PROGRAMA, AQUI ESTAN LAS OPCIONES

int main() {
    Estudiante lista[100];
    int totalAlumnos = 0;
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
                marcarAsistencia(lista, totalAlumnos);
                break;
            case 3:
                printf("Proximamente: Reporte...\n");
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
