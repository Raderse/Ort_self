#include "geral.h"
#include "mode2.h"
#include "mode3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void replace(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff){
    char *temp;
    FILE *fptr;
    int pos, k;
    if (out_file != NULL){
        fptr = fopen(out_file, "w");
        if (fptr == NULL){
            printf("Output file cannot be opened");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < lines_n; i++){ // Lines
        temp = malloc(sizeof(lines[i]));
        Replacement *head_rep = malloc(sizeof(Replacement *));
        if (temp == NULL) exit(EXIT_FAILURE);
        pos = 0;
        for (int j = 0; j < strlen(lines[i]); j++){ // Character
            if (lines[i][j] == ' ' || lines[i][j] == '\0' || lines[i][j] == '\n' || lines[i][j] == '\t'){
                if (pos > 0){
                    temp[pos] = '\0';
                    if (word_in_dict(remove_punct_word(temp), dict, dict_size) == NULL){
                        k = 0;
                        Alternative *head_alt = NULL;
                        Replacement *new = NULL;
                        head_alt = find_alternatives(remove_punct_word(temp), dict, dict_size, max_diff);
                        new->wrong = temp;
                        new->right = head_alt->word;
                        new->next = NULL;
                        while (ispunct(temp[k]) != 0)
                        {
                            strcat(new->punct, &temp[k]);
                            k++;
                        }
                        add_word(head_rep, new);
                        free_Alternative(head_alt);
                    }
                    else{
                        k = 0;
                        Alternative *head_alt = NULL;
                        Replacement *new = NULL;
                        head_alt = find_alternatives(remove_punct_word(temp), dict, dict_size, max_diff);
                        new->wrong = NULL;
                        new->right = head_alt->word;
                        new->next = NULL;
                        while (ispunct(temp[k]) != 0)
                        {
                            strcat(new->punct, &temp[k]);
                            k++;
                        }
                        add_word(head_rep, new);
                        free_Alternative(head_alt);                        
                    }
                }
            }
        }
        Replacement *final = malloc(sizeof(Replacement));
        final->next = NULL;
        final->right = NULL;
        final->wrong = NULL;
        strcpy(final->punct, "");
        int t = strlen(temp);
        while (ispunct(temp[t]) != 0)
        {
            strcat(final->punct, &temp[t]);
            t--;
        }
        add_word(head_rep, final);
        final = head_rep;
        while (final != NULL){
            printf("%s%s", head_rep->punct, head_rep->right);
            final = final->next;
        }
        free_Replacements(head_rep);
    }
    if (fptr != NULL) fclose(fptr);
}

// Returns head
Replacement *add_word(Replacement *head, Replacement *node){
    if (head = NULL){
        return node;
    }
    Replacement *current;
    current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = node;
    return head;
}

void free_Replacements(Replacement *head){
    Replacement *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->wrong);
        free(temp->right);
        free(temp);
    }
}

void print_Replacement(Replacement *head){

}
