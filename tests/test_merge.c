#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge.h"
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

TEST
do_merge_test(size_t c)
{
    size_t i;
    void *la, *ra, *r;

    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
    }

    qsort(&arint[0], c, sizeof(int), cmp_int);
    qsort(&arint[c], ARR_SZ - c, sizeof(int), cmp_int);

    la = malloc(c * sizeof(int));
    if (c) {
        ASSERT(la);
    }

    ra = malloc((ARR_SZ - c) * sizeof(int));
    if (ARR_SZ - c) {
        ASSERT(ra);
    }

    memcpy(la, &arint[0], c * sizeof(int));
    memcpy(ra, &arint[c], (ARR_SZ - c) * sizeof(int));

    r = merge(la, c, ra, ARR_SZ - c, sizeof(int), cmp_int);
    ASSERT(r);

    qsort(&arint[0], ARR_SZ, sizeof(int), cmp_int);
    ASSERT_MEM_EQ(&arint[0], r, ARR_SZ * sizeof(int));

    if (la) {
        free(la);
    }
    if (ra) {
        free(ra);
    }
    free(r);

    /*
     * printf("c - %d\n", (int)c); 
     */
    PASS();
}

TEST
do_merge_into_test(size_t c)
{
    size_t i;
    void *la, *ra, *r;

    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
    }

    qsort(&arint[0], c, sizeof(int), cmp_int);
    qsort(&arint[c], ARR_SZ - c, sizeof(int), cmp_int);
    la = malloc(c * sizeof(int));
    if (c) {
        ASSERT(la);
    }
    ra = malloc((ARR_SZ - c) * sizeof(int));
    if (ARR_SZ - c) {
        ASSERT(ra);
    }

    memcpy(la, &arint[0], c * sizeof(int));
    memcpy(ra, &arint[c], (ARR_SZ - c) * sizeof(int));

    r = merge_into(la, c, ra, ARR_SZ - c, sizeof(int), cmp_int);
    ASSERT(r);
    qsort(&arint[0], ARR_SZ, sizeof(int), cmp_int);
    ASSERT_MEM_EQ(&arint[0], r, ARR_SZ * sizeof(int));

    if (ra) {
        free(ra);
    }
    free(r);
    /*
     * printf("c - %d\n", (int)c); 
     */
    PASS();
}

SUITE(merge_suite)
{
    int i;

    for (i = 0; i < TEST_NUM; i++) {
        RUN_TESTp(do_merge_test, (rand() % ARR_SZ));
    }

    RUN_TESTp(do_merge_test, 0);
    RUN_TESTp(do_merge_test, ARR_SZ);

    for (i = 0; i < TEST_NUM; i++) {
        RUN_TESTp(do_merge_into_test, (rand() % ARR_SZ));
    }

    RUN_TESTp(do_merge_into_test, 0);
    RUN_TESTp(do_merge_into_test, ARR_SZ);
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

    GREATEST_MAIN_END();
}
