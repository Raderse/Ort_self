#ifndef MODE2_H
#define MODE2_H

typedef struct _Alternative
{
    char *word;
    int diff;
    int index;
    struct Alternative *next;
} Alternative; // type of linked list where *next points to item of index+1

void suggesting(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff, int alts);

#endif