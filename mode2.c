#include "mode2.h"
#include "geral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

int is_valid_alternative(char *word, char *dict, int *dict_size, int max_diff){

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