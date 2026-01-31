#include "geral.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Used for qsort (not case sensitive)
int compare_dic(const void *a, const void *b) {
    return strcasecmp(*(const char **)a, *(const char **)b);
}

/* 
Orders the dictionary from file and stores in storage returning
the number of words contained for easier use of bsearch 
*/
int dict_processing(char ***storage, char *file){ 
    FILE *fptr;                                   
    int wordn = 0, size = 10000, len;
    char string[size];
    fptr = fopen(file, "r");
    if (!(fptr = NULL)){
        printf("Dictionary could not be opened");
        exit(EXIT_FAILURE);
    }
    while (fgets(string,size,fptr)){
        wordn++;
    }
    *storage = calloc(wordn, sizeof(char *));
    if (!(*storage)) exit(EXIT_FAILURE);

    rewind(fptr);
    for (int i = 0; i<wordn; i++){
        len = sizer(fptr);
        (*storage)[i] = malloc(len + 1);
        if (!((*storage)[i])){
            free_dict(&(*storage), wordn);
            exit(EXIT_FAILURE);
        }
        fgets((*storage)[i],len+1,fptr);
        (*storage)[i][strcspn((*storage)[i], "\n")] = '\0';
    }
    fclose(fptr);
    qsort(*storage, wordn, sizeof(char *), compare_dic);
    return wordn;
}

// Frees space alocated to dictionary
void free_dict(char ***dict, int size){
    for (int i = 0; i<size; i++){
        free((*dict)[i]); // Frees individual lines
    }
    free(*dict); // Frees pointer
}

int sizer(FILE *fptr){
    long start;
    int temp, count = 0;
    start = ftell(fptr);
    while ((temp = fgetc(fptr)) != EOF)
    {
        count++;
        if (temp == '\n') break;
    }
    fseek(fptr, start, SEEK_SET);
    return count;    
}

int valid(char c){
    return (isalpha(c) || strchr("àáéíóúãõâêôçÀÁÉÍÓÚÃÕÂÊÔÇ",c));
}