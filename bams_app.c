#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#include "bams.h"

int
cmp_int(const void *first, const void *second)
{
    int a = *(int *) first;
    int b = *(int *) second;

    /*
     * printf("%d %d\n", a, b); 
     */
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

#define ARR_SZ 1024 * 1024 - 1
int arint[ARR_SZ] =
{0};

int
main(int argc, char *argv[])
{
    int a, b;
    size_t i;
    int min_key = INT_MAX, max_key = INT_MIN;
    BAMS *bas;
    size_t less = 0;
    size_t equal = 0;
    size_t great = 0;

    size_t less_a = 0;
    size_t equal_a = 0;
    size_t great_a = 0;
    size_t all_a = 0;

    int *less_keys;
    int *equal_keys;
    int *great_keys;
    int *all_keys;

    srand(time(NULL));
    for (i = 0; i < ARR_SZ; i++) {
        arint[i] = rand();
        if (arint[i] < min_key) {
            min_key = arint[i];
        }
        if (arint[i] > max_key) {
            max_key = arint[i];
        }
    }

    bas = bams_create(sizeof (int), cmp_int);

    for (i = 0; i < ARR_SZ; i++) {
        bams_insert(bas, &arint[i]);
    }

#if 0
    for (i = 0; i < ARR_SZ; i++) {
        if (0 == bams_contains(bas, &arint[i])) {
            printf("Error: %d not in set.\n", arint[i]);
            break;
        };
    }
#endif

    a = arint[0];
    for (i = 0; i < ARR_SZ; i++) {
        if (arint[i] < a) {
            less++;
        } else if (arint[i] > a) {
            great++;
        } else {
            equal++;
        }
    }
    assert(less == bams_count_less(bas, &a));
    printf("Less than %d: Expected %lu, %lu\n", a, less,
           bams_count_less(bas, &a));

    assert(equal == bams_count_equal(bas, &a));
    printf("Equal to %d: Expected %lu, %lu\n", a, equal,
           bams_count_equal(bas, &a));

    assert(great == bams_count_great(bas, &a));
    printf("Great than %d: Expected %lu, %lu\n", a, great,
           bams_count_great(bas, &a));

    assert(*(int *) bams_min(bas) == min_key);
    printf("Min key: %d, expected: %d\n", *(int *) bams_min(bas), min_key);

    assert(*(int *) bams_max(bas) == max_key);
    printf("Max key: %d, expected: %d\n", *(int *) bams_max(bas), max_key);

    less_keys = bams_less(bas, &a, &less_a);
    assert(less == less_a);
    for (i = 0; i < less_a; i++) {
        assert(less_keys[i] < a);
    }
    free(less_keys);

    equal_keys = bams_equal(bas, &a, &equal_a);
    printf("Equal: %lu, %lu\n", equal, equal_a);
    assert(equal == equal_a);
    for (i = 0; i < equal_a; i++) {
        assert(equal_keys[i] == a);
    }
    free(equal_keys);

    great_keys = bams_great(bas, &a, &great_a);
    assert(great == great_a);
    for (i = 0; i < great_a; i++) {
        assert(great_keys[i] > a);
    }
    free(great_keys);

    all_keys = bams_array(bas, &all_a);
    assert(ARR_SZ == all_a);
    for (i = 1; i < all_a; i++) {
        assert(all_keys[i] >= all_keys[i - 1]);
    }
    free(all_keys);

    printf("Set size: %lu\n", bams_size(bas));
    printf("Check structure result: %d\n", bams_check_structure(bas));
    bams_free(bas);

    /*
     * big set 
     */
    /*
     * bas = bams_create(sizeof (int), cmp_int); for (i = 0; i < 1024 *
     * 1024 * 32; i++) { a = rand(); bams_insert(bas, &a); } printf("Set
     * size: %lu\n", bams_size(bas)); printf("Check structure result:
     * %d\n", bams_check_structure(bas)); bams_free(bas); 
     */
    return 0;
}
