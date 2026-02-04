#include "mode1.h"
#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Finds errors in lines and prints/writes them
void find_error(char **lines, int lines_n, char **dict, int size_dict, char *out_file){
    int err_count, pos;
    char *temp; // Will store word to verify with dict
    FILE *fptr;
    char **lines_no_punct;
    lines_no_punct = remove_punct(lines, lines_n);
    if (out_file != NULL){
        fptr = fopen(out_file, "w");
        if (fptr == NULL){
            printf("Output file cannot be opened");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < lines_n; i++){ // Each line
        temp = malloc(strlen(lines[i]) + 16);
        if (temp == NULL) exit(EXIT_FAILURE);

        err_count = 0;
        pos = 0;

        for (int j = 0; j <= (int)strlen(lines_no_punct[i]); j++){ // Each character
            if (lines_no_punct[i][j] == ' ' || lines_no_punct[i][j] == '\0' || lines_no_punct[i][j] == '\n' || lines_no_punct[i][j] == '\t'){
                if (pos > 0) {
                    temp[pos] = '\0'; // Properly terminate the word string

                    if (bsearch(&temp, dict, size_dict, sizeof(char *), compare_dic) == NULL){
                        if (err_count == 0){
                            if (out_file == NULL) printf("%d: %s \n", i, lines[i]);
                            else fprintf(fptr, "%d: %s \n", i, lines[i]);
                            err_count++;
                        }
                        
                        if (out_file == NULL) printf("Erro na palavra: \"%s\" \n", temp);
                        else fprintf(fptr, "Erro na palavra: \"%s\" \n", temp);
                    }
                    pos = 0; // Reset for next word
                }
            }
            else {
                temp[pos++] = lines_no_punct[i][j];
            }
        }
        free(temp);
    }
    if (fptr != NULL) fclose(fptr);
}