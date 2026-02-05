#include "mode2.h"
#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void suggesting(char **lines, int lines_n, char **dict, int dict_size, char *out_file, int max_diff, int alts){

}

// Checks if new word is already in the list, if it is not it gets added and return is the head of the list
Alternative *add_node(Alternative *head, Alternative *new){
    Alternative *temp_before, *temp_after;
    if (in_Alternatives(head, new->word) == 1){
        return head;
    }
    if (head == NULL){ // Empty linked list
        update_index(new);
        return new;
    }
    if (new->diff < head->diff){ // Compares number of differences (priority in ordering)
        new->next = head;
        update_index(new);
        return new;
    }
    else if (new->diff == head->diff){ // If same number of differences in head and new
        if (strcasecmp(new->word,head->word) < 0){ // See if new comes first in the dictionary
            new->next = head;
            update_index(new);
            return new;
        }
    }
    temp_after = head->next;
    temp_before = head;
    while (temp_before->next != NULL){ // If new does not become the new head loop to see where it will fit
        if (temp_after->diff < new->diff){ // If the difference of new is greater than temp_after then new comes after it in the list
            temp_before = temp_after; 
            temp_after = temp_after->next; // Advances the temp nodes
            continue;
        }
        else if (temp_after->diff > new->diff){ // If the difference of new is smaller than it comes before tem_after
            temp_before->next = new; 
            new->next = temp_after; // Change pointers so that new is between temp's
            update_index(head);
            return head;
        }
        else if (temp_after->diff == new->diff){
            if (strcasecmp(temp_after->word,new->word) < 0){
                temp_before = temp_after;
                temp_after = temp_after->next;
                continue;
            }
            else{ // Functions as if (strcasemp(temp_after->word,new->word) < 0) because new->word is not in the list
                temp_before->next = new; 
                new->next = temp_after;
                update_index(head);
                return head;              
            }
        }
    }
    temp_before->next = new; // If temp_before points to NULL we reach end of list which means new becomes the new end
    update_index(head);
    return head;
}

void free_Alternative(Alternative *head){
    Alternative *temp;
    while (head != NULL) // Check if head is pointing to NULL
    {
        temp = head; // Holds the node for deletion
        head = head->next;
        free(temp->word);
        free(temp);
    }
}

int in_Alternatives(Alternative *head, char *word){
    while (head != NULL)
    {
        if (strcasecmp(head->word,word) == 0){
            return 1;
        }
        head = head->next;
    }
    return 0;
}

// For each word return the head of a list containing all valid alternatives
Alternative *find_alternatives(char *word, char **dict, int dict_size, int max_diff){
    Alternative *head = NULL;
    int len_word = strlen(word);

    for (int diff = 1; diff <= max_diff; diff++){ // Checks for each value of difference
        for (int i = 0; i < dict_size; i++){ // For each word in the dictionary
            char *dict_word = dict[i], *string = NULL;
            int len_dict_word = strlen(dict_word), found_diff = -1, index = 0;
            // While both words are equal and not over increase index
            while (word[index] != '\0' && dict_word[index] != '\0' && tolower((unsigned char)word[index]) == tolower((unsigned char)dict_word[index]))
            {
                index++; 
            }
            if (diff == 1 && dict_word[index] != '\0' && word[index] !='\0'){
                char *part = word_in_dict(&word[index], dict, dict_size);
                if (part != NULL){
                    int total_length = strlen(dict_word) + 1 + strlen(part) + 1;
                    string = malloc(total_length);
                    if (string){
                        Alternative *new = malloc(sizeof(Alternative));
                        sprintf(string, "%s %s", dict_word, part);
                        found_diff = 1;
                    }
                }
            }

            if (found_diff == -1){
                int count = 0, i_bad = index, i_dict = index;
                while (word[i_bad] != '\0' || dict_word[i_dict] != '\0')
                {
                    if (word[i_bad] == '\0'){
                        count++;
                        i_dict++;
                    }
                    else if (dict_word[i_dict] == '\0'){
                        count++;
                        i_dict++;
                    }
                    else{
                        if (strcasecmp(&word[i_bad], &dict_word[i_dict]) != 0){
                            count++;

                        }
                        i_bad++;
                        i_dict++;
                    }
                }
                if (count == diff){
                    found_diff = diff;
                }

                if (found_diff == -1 && (index + diff) <= len_dict_word){
                    if (strcasecmp(&word[index], &dict_word[index+diff]) == 0){
                        found_diff = diff;
                    }
                }

                if (found_diff == -1 && (index + diff) <= len_word){
                    if (strcasecmp(&word[index+diff], &dict_word[index]) == 0){
                        found_diff = diff;
                    }
                }

                if (found_diff == -1){ // Search word in reverse
                    int r_count = 0, r_bad = len_word - 1, r_dict = len_dict_word - 1;

                    while (r_bad >= 0 || r_dict >= 0)
                    {
                        if (r_bad < 0){
                            r_count++;
                            r_dict--;
                        }
                        else if (r_dict <0){
                            r_count++;
                            r_bad--;
                        }
                        else{
                            if (strcasecmp(&word[r_bad],&dict_word[r_dict]) != 0){
                                r_count++;
                            }
                            r_bad--;
                            r_dict--;
                        }
                    }
                    if (r_count == diff){
                        found_diff = diff;
                    }
                }
            }
            if (found_diff == diff){
                if (string == NULL){
                    string = strdup(dict_word);
                }
                if (in_Alternatives(head, string)){
                    free(string);
                }
                else{
                    Alternative *newnode = malloc(sizeof(Alternative));
                    if (newnode){
                        newnode->word = string;
                        newnode->diff = diff;
                        newnode->next = NULL;
                        head = add_node(head, newnode);
                    }
                    else{
                        free(newnode);
                    }
                }
            }
            else{
                if (string){
                    free(string);
                }
            }
        }
    }
    return head;
}

void update_index(Alternative *head){
    int previous_index = 0;
    Alternative *current_node;
    current_node = head;
    current_node->index = previous_index;
    previous_index++;
    current_node = current_node->next;
    while (current_node != NULL)
    {
        current_node->index = previous_index++;
        current_node = current_node->next;
    }
}