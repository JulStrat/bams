#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bams.h"

int cmp_int(const void *first, const void *second)
{
    int a = *(int *)first;
    int b = *(int *)second;
    // printf("%d %d\n", a, b);
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

#define ARR_SZ 1024*1024
int arint[ARR_SZ] = {0};

int main(int argc, char *argv[])
{   int a, b, i;
    BAMS *bas;

    srand(time(NULL));
    for (i = 0; i < ARR_SZ; i++)
    {   
        arint[i] = rand();
    }

    bas = bams_create(sizeof (int), cmp_int);

    for (i = 0; i < ARR_SZ; i++)
    {   
        bams_insert(bas, &arint[i]);
    }

    for (i = 0; i < ARR_SZ; i++)
    {   
        if (0 == bams_contains(bas, &arint[i]))
        {
           printf("Error: %d not in set.\n", arint[i]);
           break;
        };
    }
    
    printf("Set size: %d\n", bams_get_size(bas));
    printf("Check structure result: %d\n", bams_check_structure(bas));
    bams_free(bas);

    return 0;
}