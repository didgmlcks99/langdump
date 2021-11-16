#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void check_input();
FILE *open_file(char *gramFile);
void validate_input(int max_length);
void start_prog(FILE *file, int max_length);
char *trim(char *str);
void trim_quote(char *str);
char* my_trim(char* str);
void print_gram(char **symbols, int symb_count, char ***sequences, int seq_count);
void gram_recursive(char *target, char **symbols, int symb_count, char ***sequences, int seq_count, int max);
int symbol_exist(char *target, char **symbols, int symb_count);
int symbol_index(char *target, char **symbols, int symb_count);
char* replace_sub(char *target, char *sub, int index);

int main(int argc, char **args)
{
    char *gramFile = args[1];
    int max_length = atoi(args[2]);

    validate_input(max_length);
    FILE *fp = open_file(gramFile);

    start_prog(fp, max_length);

    fclose(fp);

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
    FILE *fp;

    fp = fopen(gramFile, "r");

    if (fp == NULL)
    {
        printf("[FILE ERROR] Cannot open file \n");
        exit(0);
    }

    return fp;
}

void validate_input(int max_length)
{
    if (max_length < 1 || max_length > 64)
    {
        printf("[INVALID INPUT] max_length must be between 1 and 64\n");
        exit(0);
    }
}

void start_prog(FILE *file, int max_length)
{
    char **symbols = (char**)malloc(100 * sizeof(char *));
    for(int i=0; i<32; i++){
        symbols[i] = (char *)malloc(16 * sizeof(char));
    }
    int symb_count = 0;

    char*** sequences = (char***)malloc(100 * sizeof(char**));
    for (int i = 0; i < 32; i++)
    {
        sequences[i] = (char**)malloc(32 * sizeof(char*));
        for (int j = 0; j < 3; j++)
        {
            sequences[i][j] = (char*)malloc(64 * sizeof(char));
        }
    }
    int seq_count = 0;

    char line[64];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char *token = strtok(line, ":==");
        token = trim(token);

        if(token[0] == 'S') {
            token = strtok(NULL, ":==");
            token = trim(token);
            trim_quote(token);
            token = my_trim(token);

            strcpy(symbols[symb_count], token);
            symb_count++;
        }else{
            strcpy(sequences[seq_count][0], token);

            token = strtok(NULL, ":==");
            token = trim(token);
            trim_quote(token);
            token = my_trim(token);

            strcpy(sequences[seq_count][1], token);

            seq_count++;
        }
    }

    print_gram(symbols, symb_count, sequences, seq_count);

    gram_recursive(symbols[0], symbols, symb_count, sequences, seq_count, max_length);
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

void trim_quote(char *str){
    for(int i=0; i<(int)strlen(str); i++){
        if(str[i] == '"') str[i] = ' ';
    }
}

char* my_trim(char* str)
{
    static char trimmed[64];
    int trimmed_count = 0;

    for(int i=0; i<(int)strlen(str); i++){
        if(str[i] != 32){
            trimmed[trimmed_count] = str[i];
            trimmed_count++;
        }
    }

    trimmed[trimmed_count] = '\0';
  
    return trimmed;
}

void print_gram(char **symbols, int symb_count, char ***sequences, int seq_count){
    printf("Symbols\n");
    for(int i=0; i<symb_count; i++){
        printf("%c\n", symbols[i][0]);
    }

    printf("\nSymbols : Expressions\n");
    for(int i=0; i<seq_count; i++){
        printf("%c : %s\n", sequences[i][0][0], sequences[i][1]);
    }

    printf("\n===========================\n\n");
}

void gram_recursive(char *target, char **symbols, int symb_count, char ***sequences, int seq_count, int max){
    if((int)strlen(target) > max){
    }else if(symbol_exist(target, symbols, symb_count) == 0){
        printf("%s\n", target);
    }else{
        int index = symbol_index(target, symbols, symb_count);
        char *send = (char*)malloc(64 * sizeof(char));

        for(int i=0; i<seq_count; i++){
            if(target[index] == sequences[i][0][0]){
                if((int)strlen(target) == 1){
                    send = sequences[i][1];
                }else{
                    send = replace_sub(target, sequences[i][1], index);
                }
                gram_recursive(send, symbols, symb_count, sequences, seq_count, max);
            }
        }
    }
}

int symbol_exist(char *target, char **symbols, int symb_count){
    for(int i=0; i<symb_count; i++){
        for(int j=0; j<(int)strlen(target); j++){
            if(target[j] == symbols[i][0]) return 1;
        }
    }
    return 0;
}

int symbol_index(char *target, char **symbols, int symb_count){
    for(int i=0; i<symb_count; i++){
        for(int j=0; j<(int)strlen(target); j++){
            if(target[j] == symbols[i][0]) return j;
        }
    }
    return 0;
}

char* replace_sub(char *target, char *sub, int index)
{
    char *result = (char*)malloc(64 * sizeof(char));

    int sub_len = (int)strlen(sub);

    for(int i=0; i<index; i++){
        result[i] = target[i];
    }

    strcat(result, sub);

    int x = index+1;
    int y = index+sub_len;
    while(x < (int)strlen(target)){
        result[y] = target[x];
        x++;
        y++;
    }

    return result;
}
