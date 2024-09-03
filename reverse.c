#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char lines[MAX_LINES][1024];
    int line_count = 0;

    // Manejar los diferentes casos de argumentos
    if (argc > 3) {
        fprintf(stderr, "Uso: %s [archivo_entrada] [archivo_salida]\n", argv[0]);
        return 1;
    }

    // Abrir los archivos según los argumentos
    if (argc == 1) {
        input = stdin;
        output = stdout;
    } else if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Error al abrir el archivo de entrada");
            return 1;
        }
        output = stdout;
    } else {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Error al abrir el archivo de entrada");
            return 1;
        }
        output = fopen(argv[2], "w");
        if (output == NULL) {
            perror("Error al abrir el archivo de salida");
            fclose(input);
            return 1;
        }
    }

    // Leer todas las líneas en el arreglo, eliminando el '\n' al final
    while (fgets(lines[line_count], sizeof(lines[line_count]), input) != NULL) {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0'; // Elimina el '\n'
        line_count++;
    }

    // Escribir las líneas en orden inverso
    for (int i = line_count - 1; i >= 0; i--) {
        fputs(lines[i], output);
        if (i > 0) { // Agrega una nueva línea al final de cada línea, excepto la última
            fputs("\n", output);
        }
    }

    // Cerrar los archivos
    fclose(input);
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}