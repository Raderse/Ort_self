#ifndef MODE3_H
#define MODE3_H

typedef struct Replacement{
    char *wrong;
    char *right;
    struct Replacement *next;
} Replacement;

void replace(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff);

#endif