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
    fptr = fopen(out_file, "w");

    for (int i = 0; i < lines_n; i++){ // Each line
        temp = malloc(strlen(lines[i]) + 16);
        if (temp == NULL) exit(EXIT_FAILURE);

        err_count = 0;
        pos = 0;

        for (int j = 0; lines[i][j] != '\0'; j++){ // Each character
            if (lines[i][j] != ' '){ // Finish logic to include cases with '
                temp[pos] = lines[i][j];
                pos++;
            }
            else{
                if (bsearch(temp, dict, size_dict, sizeof(char *), compare_dic) == NULL){
                    if (err_count == 0){
                        if (out_file == NULL){
                            printf("%d: %s \n", i, lines[i]);
                        }
                        else{
                            fprintf(fptr, "%d: %s \n", i, lines[i]);
                        }
                        err_count++;
                    }
                    if (out_file == NULL){
                        printf("Erro na palavra: \"%s\" \n", temp);
                    }
                    else{
                        fprintf(fptr, "%d: %s \n", i, lines[i]);
                    }
                }
                pos = 0;
            }
        }
    }
    free(temp);
    if (fptr != NULL) fclose(fptr);
}