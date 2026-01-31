// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// Function declarations
void print_help();


int main(int argc, char *argv[]){
    // Variables
    int opt, alt = 10, diff = 2, mode = 1;
    char *pIn_file = NULL, *pTemp_file = NULL, *pOut_file = NULL, *pDict = "words";

    while ((opt = getopt(argc, argv, "hi:o:d:a:n:m")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_help();
            break;
        
        case 'i': // Defines input file
            pIn_file = malloc(strlen(optarg)+1);
            if (!pIn_file){     // Pointers return false if = NULL
                exit(EXIT_FAILURE);
            }
            if (!(pTemp_file = fopen(pIn_file, "r"))){
                printf("Input file is cannot be opened");
                exit(EXIT_FAILURE);
            }
            fclose(pTemp_file);
            strcpy(pIn_file, optarg);
            break;
        
        case 'o': // Defines output file
            pOut_file = malloc(strlen(optarg)+1);
            if (!pOut_file){
                exit(EXIT_FAILURE);
            }
            strcpy(pOut_file, optarg);
            break;

        case 'd': // Defines dictionary
            if (!(pTemp_file = (optarg,"r"))){
                printf("Dictionary cannot be opened");
                exit(EXIT_FAILURE);
            }
            fclose(pTemp_file);
            pDict = optarg;
            break;

        case 'a': // Alternatives
            alt = atoi(optarg);
            if (alt <= 0){
                printf("Value for alternatives to display must be a number greater than 0");
                exit(EXIT_FAILURE);
            }
            break;

        case 'n': // Differences
            diff = atoi(optarg);
            if (diff <= 0){
                printf("Value for differences allowed must be a number greater than 0");
                exit(EXIT_FAILURE);
            }
            break;

        case 'm': // Mode
            mode = atoi(optarg);
            if (mode < 1 || mode > 3){
                printf("Modes available are only 1, 2 and 3");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
    
}

// Functions definitions
void print_help(){
    printf("Help");
}