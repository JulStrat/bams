#include <stdio.h>
#include <stdlib.h>
//#include <assert.h>
#include "greatest.h"

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

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
    int key;
    int *pos;

    printf("Test empty array\n");
    key = -21;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 0, sizeof (int), cmp_int);
    //assert(pos == &arr_a[0]);
    ASSERT_EQ(&arr_a[0], pos);

    key = 11;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 0, sizeof (int), cmp_int);
    //assert(pos == &arr_a[0]);
    ASSERT_EQ(&arr_a[0], pos);	

    key = 11;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 0, sizeof (int), cmp_int);
    ASSERT_FALSE(pos);

    printf("Test bisect_left\n");
    // int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};
    key = -21;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[0]);
    ASSERT_EQ(&arr_a[0], pos);

    key = -3;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[0]);
    ASSERT_EQ(&arr_a[0], pos);

    key = 11;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[2]);
    ASSERT_EQ(&arr_a[2], pos);

    key = 12;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[5]);
    ASSERT_EQ(&arr_a[5], pos);

    key = 200;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[6]);
    ASSERT_EQ(&arr_a[6], pos);

    key = 300;
    pos = NULL;
    pos = bisect_left(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert((pos - &arr_a[0]) == 7);
    ASSERT_EQ(7, pos - &arr_a[0]);

    printf("Test bisect_right\n");
    // int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};
    key = -21;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[0]);
    ASSERT_EQ(&arr_a[0], pos);

    key = -3;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[1]);
    ASSERT_EQ(&arr_a[1], pos);

    key = 11;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[5]);
    ASSERT_EQ(&arr_a[5], pos);

    key = 12;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[5]);
    ASSERT_EQ(&arr_a[5], pos);

    key = 200;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert((pos - &arr_a[0]) == 7);
    ASSERT_EQ(7, pos - &arr_a[0]);

    key = 300;
    pos = NULL;
    pos = bisect_right(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert((pos - &arr_a[0]) == 7);
    ASSERT_EQ(7, pos - &arr_a[0]);

    printf("Test bin_search\n");
    // int arr_a[7] = {-3, 7, 11, 11, 11, 101, 200};
    key = -22;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    ASSERT_FALSE(pos);

    key = -3;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[0]);
    ASSERT_EQ(&arr_a[0], pos);

    key = 11;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[2]);
    ASSERT_EQ(&arr_a[2], pos);

    key = 12;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    ASSERT_FALSE(pos);

    key = 200;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    //assert(pos == &arr_a[6]);
    ASSERT_EQ(&arr_a[6], pos);

    key = 300;
    pos = NULL;
    pos = bin_search(&key, &arr_a[0], 7, sizeof (int), cmp_int);
    ASSERT_FALSE(pos);

    printf("All tests passed.\n");
    return EXIT_SUCCESS;
}