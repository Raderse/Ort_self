#ifndef MODE3_H
#define MODE3_H

typedef struct Replacement{
    char *wrong;
    char *right;
    char punct[16];
    struct Replacement *next;
} Replacement;

void replace(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff);
Replacement *add_word(Replacement *head, Replacement *node);
void free_Replacements(Replacement *head);
void print_Replacement(Replacement *head);

#endif