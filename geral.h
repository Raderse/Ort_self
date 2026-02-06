#ifndef GERAL_H
#define GERAL_H

#include <stdio.h>

int compare_dic(const void *a, const void *b);
int dict_processing(char ***storage, char *file);
void free_dict(char ***dict, int size);
int sizer(FILE *fptr);
int valid(char c);
int reader(char ***lines, char *file);
char **remove_punct(char **lines, int lines_n);
char *word_in_dict(char *word, char **dict, int dict_size);

#endif