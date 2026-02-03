#include "mode2.h"
#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void suggesting(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff, int alts){

}

Alternative *add_node(Alternative *head, Alternative *new){

}

void free_Alternative(Alternative *head){
    Alternative *temp;
    temp = head;
    while (temp != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

int in_Alternatives(Alternative *head, char *word){
    while (head != NULL)
    {
        if (strcmp(head->word,word) == 0){
            return 1;
        }
        head = head->next;
    }
    return 0;
}