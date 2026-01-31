#ifndef GERAL_H
#define GERAL_H

#include <stdio.h>

int compare_dic(const void *a, const void *b);
int dict_processing(char ***storage, char *file);
void free_dict(char ***dict, int size);
int sizer(FILE *fptr);
int valid(char c);

#endif