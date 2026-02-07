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
        free(new->word);
        free(new);
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
Alternative *find_alternatives(char *wrong_word, char **dict, int dict_size, int max_diff){
    Alternative *head = NULL;
    int len_wrong_word = strlen(wrong_word);
    // For each difference value searches for words with that amount of differences
    for (int seeking_diff = 1; seeking_diff <= max_diff; seeking_diff++){
        for (int i = 0; i< dict_size; i++){ // For each word in the dictionary
            char *dict_word = dict[i], *string = NULL;
            int len_dict_word = strlen(dict_word), found_diff = -1, index = 0;
            // While both words are equal and not over
            while (dict_word[index] != '\0' && wrong_word[index] != '\0' && tolower(dict_word[index]) == tolower(wrong_word[index]))
            {
                index++; // Index stores the index of the first difference
            }
            // If the dictionary word already ended then the rest of the wrong_word could be
            // another word in the dictionary
            if (seeking_diff == 1 && dict_word[index] == '\0' && wrong_word[index] != '\0'){
                char *part = word_in_dict(&wrong_word[index], dict, dict_size);
                if (part != NULL){
                    int total_len = strlen(dict_word) + 1 + strlen(part) + 1; // Size of both words + a space + end of string char
                    string = malloc(total_len);
                    if (string){ // Checks if allocation was successful;
                        sprintf(string, "%s %s", dict_word, part);
                        found_diff = 1;
                    }
                }
            }
            if (found_diff == -1){ // If no differences have been found yet
                int count = 0, f_wrong = index, f_dict = index;
                while (wrong_word[f_wrong] != '\0' || dict_word[f_dict] != '\0') // While at least one word is not over
                {
                    if (wrong_word[f_wrong] == '\0'){ // If the wrong word is over (smaller than dict_word)
                        count++;  // Considers as error each letter that it is smaller
                        f_dict++; // Increments only the index for dict_word because the wrong one is over
                    }
                    else if (dict_word[f_dict] == '\0'){
                        count++;
                        f_wrong++;
                    }
                    else{ // If neither one is over
                        if (tolower(wrong_word[f_wrong]) != tolower(dict_word[f_dict])){ // And they are different
                            count++; // There is a difference
                        }
                        f_wrong++;
                        f_dict++; // Increments both indices because they are not over
                    }
                }
                if (count == seeking_diff){ // If the number of differences is what we are seeking
                    found_diff = count;     // we update the value of found differences
                }

                // If we have not found the correct number of differences and the index of the first difference +
                // the number of differences we are looking for is smaller/equal to the lenght of the dictionary
                // word we check if there is a block of seeking_diff letters missing in the middle of the wrong word
                if (found_diff == -1 && (index + seeking_diff) <= len_dict_word){
                    if (strcasecmp(&wrong_word[index], &dict_word[index+seeking_diff]) == 0){
                        found_diff = seeking_diff;
                    }
                }

                // Same logic as before but for a block of extra letters in wrong_word
                if (found_diff == -1 && (index + seeking_diff) <= len_wrong_word){
                    if (strcasecmp(&wrong_word[index+seeking_diff], &dict_word[index]) == 0){
                        found_diff = seeking_diff;
                    }
                }

                // Searching word in reverse if we have not found correct number of differences
                if (found_diff == -1){
                    int r_count = 0, r_wrong = len_wrong_word - 1, r_dict = len_dict_word - 1; // Minus one because indices start at 0
                    // If at least one word is not over
                    while (r_wrong >= 0 || r_dict >= 0)
                    {
                        if (r_wrong < 0){ // If wrong is over we only change the index of dict and count the differences
                            r_count++;
                            r_dict--;
                        }
                        else if (r_dict < 0){
                            r_count++;
                            r_wrong--;
                        }
                        else{
                            if (tolower(wrong_word[r_wrong]) != tolower(dict_word[r_dict])){ // If words are different at current index
                                r_count++;
                            }
                            r_dict--;
                            r_wrong--;
                        }
                    }
                    if (r_count == seeking_diff){
                        found_diff = r_count;
                    }
                }
            }
            // If we found the correct number of differences (safeguard but same as found_diff != -1)
            // we check if we already have a string and add a new node to the list of alternatives
            if (found_diff == seeking_diff){
                if (string == NULL){
                    string = strdup(dict_word);
                }
                Alternative *new_node = malloc(sizeof(Alternative));
                if (new_node){
                    new_node->diff = found_diff;
                    new_node->word = string;
                    new_node->next = NULL;
                    head = add_node(head, new_node);
                }
                else{
                    free(new_node);
                }
            }
            else if (string){
                free(string);
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