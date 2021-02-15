#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

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
    int min_key = INT_MAX, max_key = INT_MIN;
    BAMS *bas;
	size_t less = 0;
	size_t equal = 0;	
	size_t great = 0;	
	
    srand(time(NULL));
    for (i = 0; i < ARR_SZ; i++)
    {   
        arint[i] = rand();
        if (arint[i] < min_key)
        {
        	min_key = arint[i];
		}
		if (arint[i] > max_key)
		{
			max_key = arint[i];
		}
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

	a = arint[0];
    for (i = 0; i < ARR_SZ; i++)
    {   
        if (arint[i] < a)
        {
        	less++;
		}
		else if (arint[i] > a)
		{
			great++;
		}
		else
		{
			equal++;
		}
    }
	assert(less == bams_count_less(bas, &a));
    printf("Less than %d: Expected %d, %d\n", a, less, bams_count_less(bas, &a));
	
	assert(equal == bams_count_equal(bas, &a));	
    printf("Equal to %d: Expected %d, %d\n", a, equal, bams_count_equal(bas, &a));	
	
	assert(great == bams_count_great(bas, &a));		
    printf("Great than %d: Expected %d, %d\n", a, great, bams_count_great(bas, &a));	
    
	assert(*(int *)bams_min(bas) == min_key);
    printf("Min key: %d, expected: %d\n", *(int *)bams_min(bas), min_key);
	
	assert(*(int *)bams_max(bas) == max_key);	
    printf("Max key: %d, expected: %d\n", *(int *)bams_max(bas), max_key);

    printf("Set size: %d\n", bams_get_size(bas));
    printf("Check structure result: %d\n", bams_check_structure(bas));
    bams_free(bas);

    return 0;
}