#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bisect.h"

int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};

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

    printf("Test empty array\n");
    key = -21;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 0, sizeof (int), cmp_int);
    assert(pos == &arr_a[0]);

    key = 11;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 0, sizeof (int), cmp_int);
    assert(pos == &arr_a[0]);

    key = 11;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 0, sizeof (int), cmp_int);
    assert(!pos);

    printf("Test bisect_left\n");
    // int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};
    key = -21;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[0]);

    key = -3;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[0]);

    key = 11;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[2]);

    key = 12;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[5]);

    key = 200;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[6]);

    key = 300;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert((pos - &arr_a[0]) == 7);

    printf("Test bisect_right\n");
    // int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};
    key = -21;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[0]);

    key = -3;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[1]);

    key = 11;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[5]);

    key = 12;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[5]);

    key = 200;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert((pos - &arr_a[0]) == 7);

    key = 300;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert((pos - &arr_a[0]) == 7);

    printf("Test bin_search\n");
    // int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};
    key = -22;
    pos = 12;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(!pos);

    key = -3;
    pos = 13;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[0]);

    key = 11;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[2]);

    key = 12;
    pos = 14;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(!pos);

    key = 200;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(pos == &arr_a[6]);

    key = 300;
    pos = 17;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    assert(!pos);

    printf("All tests passed.\n");
    return EXIT_SUCCESS;
}