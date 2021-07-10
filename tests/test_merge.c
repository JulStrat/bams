
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SH_MERGE_IMPLEMENTATION
#include "sh_merge.h"
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

#define ARR_SZ 30971
int arint[ARR_SZ] =
{0};

#define TEST_NUM 128

TEST
do_merge_test(int c)
{
    size_t i;
    void *la, *ra, *r;

    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
    }

    qsort(&arint[0], c, sizeof (int), cmp_int);
    qsort(&arint[c], ARR_SZ - c, sizeof (int), cmp_int);

    la = malloc(c * sizeof (int));
    ra = malloc((ARR_SZ - c) * sizeof (int));

    memcpy(la, &arint[0], c * sizeof (int));
    memcpy(ra, &arint[c], (ARR_SZ - c) * sizeof (int));

    r = merge(la, c, ra, ARR_SZ - c, sizeof (int), cmp_int);

    ASSERT(r);

    qsort(&arint[0], ARR_SZ, sizeof (int), cmp_int);
    ASSERT_MEM_EQ(&arint[0], r, ARR_SZ * sizeof (int));

    free(la);
    free(ra);
    free(r);

    PASS();
}

TEST
do_merge_into_test(int c)
{
    size_t i;
    void *la, *ra, *r;

    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
    }

    qsort(&arint[0], c, sizeof (int), cmp_int);
    qsort(&arint[c], ARR_SZ - c, sizeof (int), cmp_int);

    la = malloc(c * sizeof (int));
    ra = malloc((ARR_SZ - c) * sizeof (int));

    memcpy(la, &arint[0], c * sizeof (int));
    memcpy(ra, &arint[c], (ARR_SZ - c) * sizeof (int));

    r = merge_into(la, c, ra, ARR_SZ - c, sizeof (int), cmp_int);

    ASSERT(r);

    qsort(&arint[0], ARR_SZ, sizeof (int), cmp_int);
    ASSERT_MEM_EQ(&arint[0], r, ARR_SZ * sizeof (int));

    free(ra);
    free(r);

    PASS();
}

SUITE(merge_suite)
{
    int i;
    int c;

    for (i = 0; i < TEST_NUM; i++) {
        c = (rand() % ARR_SZ);
        if ((c < 0) || (c > ARR_SZ))
            continue;
        RUN_TEST1(do_merge_test, c);
    }

    RUN_TEST1(do_merge_test, 0);
    RUN_TEST1(do_merge_test, ARR_SZ);
}

SUITE(merge_into_suite)
{
    int i;
    int c;

    for (i = 0; i < TEST_NUM; i++) {
        c = (rand() % ARR_SZ);
        if ((c < 0) || (c > ARR_SZ))
            continue;
        RUN_TEST1(do_merge_into_test, c);
    }

    RUN_TEST1(do_merge_into_test, 0);
    RUN_TEST1(do_merge_into_test, ARR_SZ);
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

    RUN_SUITE(merge_suite);
    RUN_SUITE(merge_into_suite);

    GREATEST_MAIN_END();
}
