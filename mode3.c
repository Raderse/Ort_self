#include "geral.h"
#include "mode2.h"
#include "mode3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void replace(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff){
    char *temp;
    FILE *fptr = NULL;
    int pos;
    if (out_file != NULL){
        fptr = fopen(out_file, "w");
        if (fptr == NULL){
            printf("Output file cannot be opened");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < lines_n; i++){ // Lines
        temp = malloc(strlen(lines[i]) + 1);
        Replacement *head_rep = NULL;
        if (temp == NULL) exit(EXIT_FAILURE);
        pos = 0;
        for (int j = 0; j <= strlen(lines[i]); j++){ // Character
            if (lines[i][j] == ' ' || lines[i][j] == '\0' || lines[i][j] == '\n' || lines[i][j] == '\t'){
                if (pos > 0){
                    temp[pos] = '\0';
                    Replacement *new_node = malloc(sizeof(Replacement));
                    new_node->punct[0] = '\0'; 
                    new_node->next = NULL;
                    char *clean = remove_punct_word(temp);
                    if (word_in_dict(clean, dict, dict_size) == NULL){
                        Alternative *head_alt = find_alternatives(clean, dict, dict_size, max_diff);
                        new_node->wrong = strdup(temp);
                        if (head_alt != NULL) {
                            new_node->right = strdup(head_alt->word);
                            free_Alternative(head_alt);
                        } else {
                            new_node->right = strdup(clean);
                        }
                    } else {
                        new_node->wrong = NULL;
                        new_node->right = strdup(clean);
                    }
                    int p_start = strlen(clean);
                    strcpy(new_node->punct, &temp[p_start]);
                    int p_len = strlen(new_node->punct);
                    if (lines[i][j] != '\0') {
                        new_node->punct[p_len] = lines[i][j];
                        new_node->punct[p_len+1] = '\0';
                    }

                    free(clean);
                    head_rep = add_word(head_rep, new_node);
                    pos = 0;
                }
            }
            else{
                temp[pos++] = lines[i][j];
            }
        }
        Replacement *curr = head_rep;
        while (curr != NULL) {
            if (fptr == NULL) {
                printf("%s%s", curr->right, curr->punct);
            } else {
                fprintf(fptr, "%s%s", curr->right, curr->punct);
            }
            curr = curr->next;
        }
        if (fptr == NULL){
            printf("\n");
        }
        else{
            fprintf(fptr, "\n");
        }
        free_Replacements(head_rep);
        free(temp);
    }
    if (fptr != NULL) fclose(fptr);
}

// Returns head
Replacement *add_word(Replacement *head, Replacement *node){
    if (head == NULL){
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