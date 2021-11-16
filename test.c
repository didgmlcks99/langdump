#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool bin_pal(int *num, int size);
bool is_pal(int *bin_num, int size);

int main(int argc, char **args)
{

    // int max_length = atoi(args[1]);

    // if(max_length >64 || max_length < 1){
    //     printf("A string is a finite sequence of zero or up to 64 characters.\n");
    //     exit(1);
    // }

    int max_length = 6;
    int bin_num[max_length];

    bin_pal(bin_num, 0);

    return 0;
}

bool bin_pal(int *num, int size)
{
    if (size == 6)
    {
        return true;
    }
    else
    {
        num[size] = 0;
        if (is_pal(num, size + 1) == true)
        {
            for (int i = 0; i < size + 1; i++)
            {
                printf("%d", num[i]);
            }
            printf("\n");
        }
        bin_pal(num, size + 1);

        num[size] = 1;
        if (is_pal(num, size + 1) == true)
        {
            for (int i = 0; i < size + 1; i++)
            {
                printf("%d", num[i]);
            }
            printf("\n");
        }
        bin_pal(num, size + 1);
    }

    return true;
}

bool is_pal(int *bin_num, int size)
{
    int l = 0;
    int r = size - 1;

    while (l < r)
    {
        if (bin_num[l++] != bin_num[r--])
        {
            return false;
        }
    }

    return true;
}
