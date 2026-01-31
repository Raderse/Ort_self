#include "geral.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare_dic(const void *a, const void *b) {
    return strcasecmp(*(const char **)a, *(const char **)b);
}

int dict_processing(char *dict, char *path){
    
}