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
    while(getchar() != '\n'); // Limpieza de buffer

    printf("Ingrese Nombre Completo: ");
    fgets(lista[*contador].nombre, 50, stdin);
    lista[*contador].nombre[strcspn(lista[*contador].nombre, "\n")] = 0;

    // Inicializamos la asistencia de todo el mes en 0 (Falta)
    for(int i = 0; i < 31; i++) {
        lista[*contador].asistencia[i] = 0;
    }
    
    lista[*contador].activo = 1; // El estudiante nace "Activo"
    (*contador)++; 
    
    printf("\n[+] Estudiante registrado exitosamente.\n");
}

void pasarAsistenciaDiaria(Estudiante lista[], int contador) {
    int dia;
    if (contador == 0) {
        printf("\n[!] No hay estudiantes registrados.\n");
        return;
    }

    printf("\n--- Pase de Lista Diario ---\n");
    printf("Ingrese el dia del mes (1 al 31): ");
    
    if (scanf("%d", &dia) != 1 || dia < 1 || dia > 31) {
        printf("[!] Dia invalido. Debe ser entre 1 y 31.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    printf("\nPasando asistencia para el dia %d...\n", dia);
    int hayActivos = 0;

    // Recorremos toda la lista preguntando por cada alumno activo
    for (int i = 0; i < contador; i++) {
        if (lista[i].activo == 1) {
            hayActivos = 1;
            int estado;
            printf("ID: %d | %s -> (1 = Presente, 0 = Falta): ", lista[i].id, lista[i].nombre);
            
            if (scanf("%d", &estado) != 1) {
                while(getchar() != '\n');
                estado = 0; // Si el profe teclea mal, cuenta como falta por seguridad
            }
            
            // Guardamos en el día correcto (dia-1 porque los arreglos empiezan en 0)
            lista[i].asistencia[dia - 1] = (estado == 1) ? 1 : 0;
        }
    }

    if (!hayActivos) {
        printf("[!] Todos los estudiantes estan dados de baja.\n");
    } else {
        printf("\n[OK] Asistencia del dia %d guardada.\n", dia);
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
    FILE *archivo = fopen("../data/reporte_mensual.txt", "w");
    if (archivo == NULL) {
        printf("\n[!] Error al crear el reporte en data/.\n");
        return;
    }

    fprintf(archivo, "=================================================================================\n");
    fprintf(archivo, "                           REPORTE DE ASISTENCIA MENSUAL\n");
    fprintf(archivo, "=================================================================================\n");
    
    // Encabezado de los días
    fprintf(archivo, "%-6s | %-20s | ", "ID", "NOMBRE");
    for(int d = 1; d <= 31; d++) {
        fprintf(archivo, "%02d ", d); // Imprime 01, 02, 03...
    }
    fprintf(archivo, "\n---------------------------------------------------------------------------------\n");

    for (int i = 0; i < contador; i++) {
        if (lista[i].activo == 1) {
            fprintf(archivo, "%-6d | %-20s | ", lista[i].id, lista[i].nombre);
            for(int d = 0; d < 31; d++) {
                // Si es 1 imprime 'P', si es 0 imprime '-'
                char marca = (lista[i].asistencia[d] == 1) ? 'P' : '-';
                fprintf(archivo, " %c ", marca);
            }
            fprintf(archivo, "\n");
        }
    }

    fclose(archivo);
    printf("\n[OK] Reporte generado exitosamente en: data/reporte_mensual.txt\n");
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