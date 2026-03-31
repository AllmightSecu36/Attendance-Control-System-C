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

//AQUI SE GENERAN LOS REPORTES

void generarReporte(Estudiante lista[], int contador) {
    if (contador == 0) {
        printf("\n[!] No hay datos para generar el reporte.\n");
        return;
    }

    // Intentamos abrir (o crear) el archivo en la carpeta data
    FILE *archivo = fopen("../data/reporte_asistencia.txt", "w");

    if (archivo == NULL) {
        printf("\n[!] Error: No se pudo crear el archivo en 'data/'.\n");
        printf("Asegurate de que la carpeta 'data' exista.\n");
        return;
    }

    fprintf(archivo, "========================================\n");
    fprintf(archivo, "       REPORTE DE ASISTENCIA\n");
    fprintf(archivo, "========================================\n");
    fprintf(archivo, "ID\tESTADO\t\tNOMBRE\n");
    fprintf(archivo, "----------------------------------------\n");

    for (int i = 0; i < contador; i++) {
        // Usamos nuestro "interruptor" para escribir el texto
        char *estado = (lista[i].presente == 1) ? "PRESENTE" : "FALTA   ";
        
        fprintf(archivo, "%d\t%s\t%s\n", lista[i].id, estado, lista[i].nombre);
    }

    fprintf(archivo, "----------------------------------------\n");
    fprintf(archivo, "Total de alumnos: %d\n", contador);

    fclose(archivo); // ¡Siempre hay que cerrar el archivo!
    printf("\n[CORRECTO] Reporte generado en: data/reporte_asistencia.txt\n");
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
                generarReporte(lista, totalAlumnos);
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
