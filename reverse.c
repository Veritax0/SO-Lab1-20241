/*  
    Integrantes:
    Juan Manuel Vera Osorio  CC 1000416823
    Valentina Cadena Zapata  CC 1000099120
*/

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
        fprintf(stderr, "usage: reverse <input> <output>\n", argv[0]);
        return 1;
    }

    // Abrir los archivos según los argumentos
    if (argc == 1) {
        input = stdin;
        output = stdout;
    } else if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n", argv[0]);
            return 1;
        }
        output = stdout;
    } else {
        if (strcmp(argv[1], argv[2]) == 0){
            fprintf(stderr, "reverse: input and output file must differ\n", argv[0]);
            return 1;
        }
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n", argv[0]);
            return 1;
        }
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "reverse: cannot open file '/no/such/file.txt'\n", argv[0]);
            fclose(input);
            return 1;
        }        
    }

    // Lee y guarda las lineas sin el salto de linea
    while (fgets(lines[line_count], sizeof(lines[line_count]), input) != NULL) {
        lines[line_count][strcspn(lines[line_count], "\n")] = '\0'; // Elimina el '\n'
        line_count++;
    }

    // Escribe las lineas en orden inverso
    for (int i = line_count - 1; i >= 0; i--) {
        fputs(lines[i], output);
        if (i > 0) { // Agrega una nueva linea cada vez, excepto la ultima
            fputs("\n", output);
        }
    }

    // Cerrar archivos
    fclose(input);
    if (output != stdout) {
        fclose(output);
    }

    return 0;
}