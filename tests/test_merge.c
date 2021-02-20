#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bisect.h"

int arr[][2] = {
	{1, 7},
	{2, 16},
	{4, 9},
	{-11, 20}
};
	
int cmp_int(const void *first, const void *second)
{
    int a = *(int *)first;
    int b = *(int *)second;

    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    int key;
    int *pos;
	int *r;

	/* {1, 7}, {2, 16} */
	r = merge(arr[0], 2, arr[1], 2, sizeof(int), cmp_int);
    assert(r[0] == 1);
    assert(r[1] == 2);		
    assert(r[2] == 7);
    assert(r[3] == 16);		
	free(r);

	/* {1}, {2, 16} */	
	r = merge(arr[0], 1, arr[1], 2, sizeof(int), cmp_int);
    assert(r[0] == 1);
    assert(r[1] == 2);		
    assert(r[2] == 16);		
	free(r);

	/* {}, {2, 16} */
	r = merge(arr[0], 0, arr[1], 2, sizeof(int), cmp_int);
    assert(r[0] == 2);
    assert(r[1] == 16);		
	free(r);

	/* {}, {2} */	
	r = merge(arr[0], 0, arr[1], 1, sizeof(int), cmp_int);
    assert(r[0] == 2);
	free(r);

	/* NULL, {2} */	
	r = merge(NULL, 0, arr[1], 1, sizeof(int), cmp_int);
    assert(r[0] == 2);
	free(r);

	/* {1}, {} */	
	r = merge(arr[0], 1, arr[1], 0, sizeof(int), cmp_int);
    assert(r[0] == 1);
	free(r);

	/* {1}, NULL */	
	r = merge(arr[0], 1, NULL, 0, sizeof(int), cmp_int);
    assert(r[0] == 1);
	free(r);

    printf("All tests passed.\n");
    return EXIT_SUCCESS;
}