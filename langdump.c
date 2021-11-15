#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void check_input();
FILE *open_file(char *gramFile);
void validate_input(int max_length);

int main(int argc, char **args)
{
    char *gramFile = args[1];
    int max_length = atoi(args[2]);

    validate_input(max_length);
    FILE *fptr = openFile(gramFile);

    

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

    char line;
    line = fgetc(fptr);
    while (line != EOF)
    {
        printf("%c", line);
        line = fgetc(fptr);
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