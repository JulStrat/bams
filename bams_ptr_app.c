#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#include "bams.h"

int
cmp_str(const void *first, const void *second)
{
    return strcmp(*(char **) first, *(char **) second);
}

int
main(int argc, char *argv[])
{
    BAMS *bas;
    char **keys;
    size_t bas_sz = 0;
    int i;

    /*
     * for (i = 1; i < argc; i++) { printf("%s\n", argv[i]); } 
     */
    bas = bams_create(0, cmp_str);
    for (i = 1; i < argc; i++) {
        bams_insert(bas, argv[i]);
    }
    keys = bams_array(bas, &bas_sz);
    for (i = 0; i < bas_sz; i++)
        printf("%s\n", keys[i]);

    printf("Min key: %s\n", bams_min(bas));
    printf("Max key: %s\n", bams_max(bas));

    free(keys);

    printf("Set size: %lu\n", bams_size(bas));
    printf("Check structure result: %d\n", bams_check_structure(bas));

    bams_clear(bas);

    for (i = 1; i < argc; i++) {
        bams_insert(bas, argv[i]);
    }
    keys = bams_array(bas, &bas_sz);
    for (i = 0; i < bas_sz; i++)
        printf("%s\n", keys[i]);

    printf("Min key: %s\n", bams_min(bas));
    printf("Max key: %s\n", bams_max(bas));

    free(keys);

    printf("Set size: %lu\n", bams_size(bas));
    printf("Check structure result: %d\n", bams_check_structure(bas));

    bams_free(bas);
    /*
     * qsort(&argv[1], argc-1, sizeof (char *), cmp_str); for (i = 1; i <
     * argc; i++) { printf("%s\n", argv[i]); } 
     */
    return 0;
}
