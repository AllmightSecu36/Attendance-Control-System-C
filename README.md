# Attendance-Control-System-C
Es una lista de control de asistencias,Permite registrar alumnos, marcar asistencia por fecha y generar un reporte final en un archivo

El sistema permite gestionar la asistencia de estudiantes de manera eficiente, utilizando archivos binarios para que los datos no se pierdan al cerrar el programa.

🚀Características principales:

Registro de Estudiantes: Permite dar de alta alumnos con ID y nombre completo.

Pase de Lista por Fecha: Registro de asistencia flexible ingresando fechas específicas (ej: 02/05/2026).

Persistencia de Datos: Los datos se guardan en un archivo binario (.dat), permitiendo que la información se mantenga entre sesiones.

Borrado Lógico: Opción para dar de baja a estudiantes sin eliminarlos físicamente del historial.

Generación de Reportes: Exporta un reporte detallado en formato .txt con el historial de cada alumno.

📁Estructura del Proyecto:
El código sigue una arquitectura modular para facilitar su mantenimiento:

src/: Contiene el código fuente (.c).

include/: Archivos de cabecera (.h) con las definiciones de estructuras.

data/: Carpeta donde se almacenan la base de datos binaria y los reportes generados.

bin/: Directorio destinado al archivo ejecutable compilado.

🛠️ Compilación y Ejecución
Para compilar este proyecto, asegúrate de tener instalado un compilador de C (como GCC/MinGW).
1. Compilar:
Desde la terminal en la carpeta raíz del proyecto, ejecuta: ./bin/asistencia
2. Ejecutar:
./bin/asistencia

📝 Nota sobre el uso
Al ser un sistema con rutas relativas, asegúrate de ejecutar el programa siempre desde la carpeta src o la carpeta raíz para que pueda localizar correctamente la carpeta data/.
