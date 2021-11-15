#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void check_input();
FILE *open_file(char *gramFile);
void validate_input(int max_length);

void start_bin(FILE *file, int max_length);
char *trim(char *str);
void *trim_quote(char *str);

int main(int argc, char **args)
{
    char *gramFile = args[1];
    int max_length = atoi(args[2]);

    validate_input(max_length);
    FILE *fptr = open_file(gramFile);

    int prob_num = 0;
    if (strcmp(gramFile, "bi_gram.txt") == 0)
    {
        prob_num = 1;
    }
    else if (strcmp(gramFile, "par_gram.txt") == 0)
    {
        prob_num = 2;
    }
    else if (strcmp(gramFile, "arith_gram.txt") == 0)
    {
        prob_num = 3;
    }

    // printf("%d\n", (int)('"'));
    start_bin(fptr, max_length);

    // switch (prob_num)
    // {
    // case 1:
    //     start_bin(fptr, rules, max_length);
    //     break;
    // case 2:
    //     break;
    // case 3:
    //     break;
    // default:
    //     break;
    // }

    fclose(fptr);
    return 0;
}

void check_input(int argc, char **args)
{
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("%d. %s\n", i + 1, args[i]);
    }
}

FILE *open_file(char *gramFile)
{
    FILE *fptr;

    fptr = fopen(gramFile, "r");

    if (fptr == NULL)
    {
        printf("[FILE ERROR] Cannot open file \n");
        exit(0);
    }

    return fptr;
}

void validate_input(int max_length)
{
    if (max_length < 1 || max_length > 64)
    {
        printf("[INVALID INPUT] max_length must be between 1 and 64\n");
        exit(0);
    }
}

void start_bin(FILE *file, int max_length)
{
    char symbols[32][2];
    int symb_count = 0;

    char sequences[32][64];
    int seq_count = 0;

    char line[64];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, ":==");
        token = trim(token);
        strcpy(symbols[symb_count], token);
        symb_count++;

        token = strtok(NULL, ":==");
        token = trim(token);
        
        // trim_quote(token);
        strcpy(sequences[seq_count], token);
        seq_count++;
    }

    for(int i=0; i<symb_count; i++){
        printf("%s : %s\n", symbols[i], sequences[i]);
    }
}

// https://www.delftstack.com/ko/howto/c/trim-string-in-c/
char *trim(char *str)
{
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

void *trim_quote(char *str){
    // char *token = strtok(str, "\"");
    // while (token != NULL)  
    // {
    //     printf("%s\n", token);
    //     // Your deletion logic goes here.
    //     token = strtok(NULL, "\"");
    // }
    // char str1[99];
    // int j=0;
    // for(int i=0; i<strlen(str); i++){
    //     printf("%d", (int)str[i]);
    //     // if(str[i] == (int)'"'){
    //     //     printf("%c\n", i);
    //     // }
    // }printf("\n");

    // printf("%s\n", str1);

    // return str;
    // char *end;

    // while((unsigned char)*str == '"') str++;

    // if(*str == 0)
    //     return str;

    // end = str + strlen(str) - 1;
    // while(end > str && (unsigned char)*end == '"') end--;

    // end[1] = '\0';

    // return str;
}