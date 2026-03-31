#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/asistencia.h" // Conectamos con nuestro archivo de cabecera

// =========================================================
// FUNCIONES DE PERSISTENCIA (GUARDAR Y CARGAR)
// =========================================================
void cargarDatos(Estudiante lista[], int *contador) {
    // Intentamos abrir el archivo binario en modo lectura ("rb")
    FILE *archivo = fopen("../data/estudiantes.dat", "rb");
    if (archivo == NULL) {
        *contador = 0; // Si no existe, empezamos desde cero
        return;
    }
    // Leemos la cantidad de alumnos y luego el arreglo completo
    fread(contador, sizeof(int), 1, archivo);
    fread(lista, sizeof(Estudiante), *contador, archivo);
    fclose(archivo);
}

void guardarDatos(Estudiante lista[], int contador) {
    // Abrimos en modo escritura binaria ("wb")
    FILE *archivo = fopen("../data/estudiantes.dat", "wb");
    if (archivo == NULL) {
        printf("\n[!] Error: No se pudo acceder a la carpeta 'data/'.\n");
        return;
    }
    fwrite(&contador, sizeof(int), 1, archivo);
    fwrite(lista, sizeof(Estudiante), contador, archivo);
    fclose(archivo);
}

// =========================================================
// INTERFAZ Y MENÚ
// =========================================================
void mostrarMenu() {
    printf("\n========================================");
    printf("\n   SISTEMA DE ASISTENCIA MENSUAL");
    printf("\n========================================");
    printf("\n1. Registrar nuevo estudiante");
    printf("\n2. Pase de lista diario");
    printf("\n3. Borrar estudiante (Dar de baja)");
    printf("\n4. Generar reporte mensual (.txt)");
    printf("\n5. Salir");
    printf("\nSeleccione una opcion: ");
}

// =========================================================
// FUNCIONES PRINCIPALES
// =========================================================
void registrarEstudiante(Estudiante lista[], int *contador) {
    if (*contador >= 100) {
        printf("\n[!] Error: Capacidad maxima alcanzada.\n");
        return;
    }

    printf("\n--- Registro de Estudiante ---\n");
    printf("Ingrese ID (Solo numeros): ");
    if (scanf("%d", &lista[*contador].id) != 1) {
        printf("[!] ID invalido.\n");
        while(getchar() != '\n'); 
        return;
    }
    while(getchar() != '\n'); 

    printf("Ingrese Nombre Completo: ");
    fgets(lista[*contador].nombre, 50, stdin);
    lista[*contador].nombre[strcspn(lista[*contador].nombre, "\n")] = 0;

    // El estudiante nuevo inicia con 0 clases registradas
    lista[*contador].totalClases = 0; 
    lista[*contador].activo = 1; 
    (*contador)++; 
    
    printf("\n[+] Estudiante registrado exitosamente.\n");
}

void pasarAsistenciaDiaria(Estudiante lista[], int contador) {
    if (contador == 0) {
        printf("\n[!] No hay estudiantes registrados.\n");
        return;
    }

    char fechaActual[15];
    printf("\n--- Pase de Lista ---\n");
    printf("Ingrese la fecha de hoy (Ej: 02/05/2026): ");
    scanf("%14s", fechaActual);
    while(getchar() != '\n'); // Limpiar buffer

    printf("\nPasando asistencia para la fecha: %s\n", fechaActual);
    int hayActivos = 0;

    for (int i = 0; i < contador; i++) {
        if (lista[i].activo == 1) {
            hayActivos = 1;
            int estado;
            printf("ID: %d | %s -> (1 = Presente, 0 = Falta): ", lista[i].id, lista[i].nombre);
            
            if (scanf("%d", &estado) != 1) {
                while(getchar() != '\n');
                estado = 0; 
            }
            
            // ¿En qué posición del historial lo guardamos? En la que indique totalClases
            int indiceClase = lista[i].totalClases;
            
            // Copiamos la fecha que escribiste al historial del alumno
            strcpy(lista[i].historial[indiceClase].fecha, fechaActual);
            lista[i].historial[indiceClase].presente = (estado == 1) ? 1 : 0;
            
            // Sumamos 1 al contador de clases de este alumno
            lista[i].totalClases++;
        }
    }

    if (!hayActivos) {
        printf("[!] Todos los estudiantes estan dados de baja.\n");
    } else {
        printf("\n[OK] Asistencia del %s guardada.\n", fechaActual);
    }
}

void borrarEstudiante(Estudiante lista[], int contador) {
    int idBuscar, encontrado = 0;

    printf("\n--- Dar de Baja Estudiante ---\n");
    printf("Ingrese el ID del estudiante a borrar: ");
    if (scanf("%d", &idBuscar) != 1) {
        while(getchar() != '\n');
        return;
    }

    for (int i = 0; i < contador; i++) {
        if (lista[i].id == idBuscar && lista[i].activo == 1) {
            lista[i].activo = 0; // Borrado Lógico
            encontrado = 1;
            printf("\n[OK] El estudiante %s ha sido dado de baja.\n", lista[i].nombre);
            break;
        }
    }

    if (!encontrado) {
        printf("\n[!] Estudiante no encontrado o ya estaba dado de baja.\n");
    }
}

void generarReporteMensual(Estudiante lista[], int contador) {
    FILE *archivo = fopen("../data/reporte_fechas.txt", "w");
    if (archivo == NULL) {
        printf("\n[!] Error al crear el reporte.\n");
        return;
    }

    fprintf(archivo, "========================================================\n");
    fprintf(archivo, "           REPORTE DE ASISTENCIA POR FECHAS\n");
    fprintf(archivo, "========================================================\n\n");
    
    // Imprimimos el reporte formato Lista por cada alumno
    for (int i = 0; i < contador; i++) {
        if (lista[i].activo == 1) {
            fprintf(archivo, "ALUMNO: %s (ID: %d)\n", lista[i].nombre, lista[i].id);
            fprintf(archivo, "--------------------------------------------------------\n");
            
            if (lista[i].totalClases == 0) {
                fprintf(archivo, "  Sin registros de asistencia aun.\n");
            } else {
                for(int c = 0; c < lista[i].totalClases; c++) {
                    char *estado = (lista[i].historial[c].presente == 1) ? "PRESENTE" : "FALTA";
                    fprintf(archivo, "  Fecha: %-12s | Estado: %s\n", lista[i].historial[c].fecha, estado);
                }
            }
            fprintf(archivo, "\n");
        }
    }

    fclose(archivo);
    printf("\n[OK] Reporte generado exitosamente en: data/reporte_fechas.txt\n");
}
// =========================================================
// FUNCIÓN PRINCIPAL (MAIN)
// =========================================================
int main() {
    Estudiante lista[100];
    int totalAlumnos = 0;
    int opcion;

    cargarDatos(lista, &totalAlumnos); // Cargamos la info al abrir el programa

    do {
        mostrarMenu();
        
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 0; 
        }

        switch(opcion) {
            case 1:
                registrarEstudiante(lista, &totalAlumnos);
                guardarDatos(lista, totalAlumnos); // Guardamos auto
                break;
            case 2:
                pasarAsistenciaDiaria(lista, totalAlumnos);
                guardarDatos(lista, totalAlumnos); // Guardamos auto
                break;
            case 3:
                borrarEstudiante(lista, totalAlumnos);
                guardarDatos(lista, totalAlumnos); // Guardamos auto
                break;
            case 4:
                generarReporteMensual(lista, totalAlumnos);
                break;
            case 5:
                guardarDatos(lista, totalAlumnos); // Guardado de seguridad final
                printf("\nDatos guardados. ¡Saliendo del sistema!\n");
                break;
            default:
                if (opcion != 0) printf("\n[!] Opcion no valida.\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}