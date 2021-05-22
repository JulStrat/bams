#include <stdio.h>
#include <stdlib.h>

#include "bisect.h"
#include "greatest.h"

int
cmp_int(const void *first, const void *second)
{
    int a = *(int *) first;
    int b = *(int *) second;

    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

#define ARR_SZ 1024 * 1024 - 1
int arint[ARR_SZ] = { 0 };
#define TEST_NUM 64

void *
lfind_ge(const void *key, const void *arr, size_t el_num, size_t el_size,
         int (*compare) (const void *, const void *))
{
    char *off = (char *) arr;
    char *high = off + el_num * el_size;
    int t;

    while (off < high) {
        t = (*compare) (key, off);
        if ((t == 0) || (t < 0)) {
            return off;
        }
        off += el_size;
    }

    return off;
}

void *
lfind_gt(const void *key, const void *arr, size_t el_num, size_t el_size,
         int (*compare) (const void *, const void *))
{
    char *off = (char *) arr;
    char *high = off + el_num * el_size;
    int t;

    while (off < high) {
        t = (*compare) (key, off);
        if (t < 0) {
            return off;
        }
        off += el_size;
    }

    return off;
}

TEST
do_bisect_left_test()
{
    size_t i;
    int r;

    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
    }

    qsort(&arint[0], ARR_SZ, sizeof(int), cmp_int);
    for (i = 0; i < TEST_NUM; i++) {
        r = rand();
        ASSERT_EQ(lfind_ge(&r, &arint[0], ARR_SZ, sizeof(int), cmp_int),
                  bisect_left(&r, &arint[0], ARR_SZ, sizeof(int),
                              cmp_int));
    }

    PASS();
}

TEST
do_bisect_right_test()
{
    size_t i;
    int r;

    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
    }

    qsort(&arint[0], ARR_SZ, sizeof(int), cmp_int);
    for (i = 0; i < TEST_NUM; i++) {
        r = rand();
        ASSERT_EQ(lfind_gt(&r, &arint[0], ARR_SZ, sizeof(int), cmp_int),
                  bisect_right(&r, &arint[0], ARR_SZ, sizeof(int),
                               cmp_int));
    }

    PASS();
}

TEST
do_bisect_min_max()
{
    size_t i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < ARR_SZ; j++) {
            arint[j] = rand();
        }
        qsort(&arint[0], ARR_SZ, sizeof(int), cmp_int);

        /*
         * min 
         */
        ASSERT_EQ(lfind_gt
                  (&arint[0], &arint[0], ARR_SZ, sizeof(int), cmp_int),
                  bisect_right(&arint[0], &arint[0], ARR_SZ, sizeof(int),
                               cmp_int));
        ASSERT_EQ(lfind_ge
                  (&arint[0], &arint[0], ARR_SZ, sizeof(int), cmp_int),
                  bisect_left(&arint[0], &arint[0], ARR_SZ, sizeof(int),
                              cmp_int));

        /*
         * max 
         */
        ASSERT_EQ(lfind_gt
                  (&arint[ARR_SZ - 1], &arint[0], ARR_SZ, sizeof(int),
                   cmp_int), bisect_right(&arint[ARR_SZ - 1], &arint[0],
                                          ARR_SZ, sizeof(int), cmp_int));
        ASSERT_EQ(lfind_ge
                  (&arint[ARR_SZ - 1], &arint[0], ARR_SZ, sizeof(int),
                   cmp_int), bisect_left(&arint[ARR_SZ - 1], &arint[0],
                                         ARR_SZ, sizeof(int), cmp_int));
    }

    PASS();
}

SUITE(bisect_suite)
{
    int i;

    for (i = 0; i < TEST_NUM; i++) {
        RUN_TEST(do_bisect_left_test);
    }

    for (i = 0; i < TEST_NUM; i++) {
        RUN_TEST(do_bisect_right_test);
    }

    for (i = 0; i < TEST_NUM; i++) {
        RUN_TEST(do_bisect_min_max);
    }
}

GREATEST_MAIN_DEFS();
int
main(int argc, char *argv[])
{
    GREATEST_MAIN_BEGIN();
#if defined(__STDC_VERSION__)
    printf("Compiler Standard version - %ld\n", __STDC_VERSION__);
#endif

    srand(time(NULL));

    RUN_SUITE(bisect_suite);

    GREATEST_MAIN_END();
}
