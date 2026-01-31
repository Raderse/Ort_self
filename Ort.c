// Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "geral.h"
#include "mode1.h"

// Function declarations
void print_help();


int main(int argc, char *argv[]){
    // Variables
    int opt, alt = 10, diff = 2, mode = 1, dict_size, line_n;
    char *pIn_file = NULL, *pOut_file = NULL, *pDict_name = "words", *pDict= NULL, **lines = NULL;
    FILE *pTemp_file;

    // Optional arguments for execution
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
            if (!(pTemp_file = fopen(optarg,"r"))){
                printf("Dictionary cannot be opened");
                exit(EXIT_FAILURE);
            }
            fclose(pTemp_file);
            pDict_name = optarg;
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
    dict_size = dict_processing(&pDict, pDict_name);

    line_n = reader(&lines, pIn_file);
    switch (mode)
    {
    case 1:
        
        break;
    
    case 2:

        break;

    case 3:

        break;
    }
}

// Functions definitions
void print_help(){
    printf("Uso correto: ./ortografia -h {help} -a {alternativas} -m {modo} -i {ficheiro in} -o {ficheiro out} -d {dicionario} -n {diferenças}\n"
        "Opções:\n\v"
        "\t-h --- apresenta a mensagem de ajuda\n"
        "\t-a --- numero maximo de alternativas a apresentar, por omissão são 10\n"
        "\t-m --- modo do corretor ortografia de 1 a 3\n"
        "\t-i --- ficheiro de texto a corrigir caso não seja dada está opção sera lido pelo terminal\n"
        "\t-o --- ficheiro de saida apresentando a resposta dependendo do modo, caso nao seja dado sera apresentado no terminal\n"
        "\t-d --- dicionario a ser utilizado por padrão usara o dicionario words\n"
        "\t-n --- numero maximo de difenças para ser aceite, por omissão é 2\n\v"
        "Modo 1: O modo 1 deteta os erros encontradados em cada linha de texto, o mesmo apresenta primeiramente a linha e depois apresenta os erros\n"
        "Modo 2: O modo 2 deteta também os erros de cada frase mas também vai apresentar sugestões de alternativas para cada palavra errada seguindo o numero maximo\n"
        "de diferenças e seguindo o numero maximo de sugestoes\n"
        "Modo 3: O modo 3 pega na primeira alternativa do modo 2 e corrige pela palavra errada no ficheiro de texto\n");
}