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
main(int argc, char *argv[]) {
    BAMS *bas;
    char **keys;
    size_t bas_sz = 0;    
    int i;
    FILE *shuff;
    char bf[1024];
    char *key;

    shuff = fopen(argv[1], "r");
    bas = bams_create(0, cmp_str);

    while (fgets(bf, 1024, shuff)) {
        key = malloc(strlen(bf)+1);
        strcpy(key, bf);
        bams_insert(bas, key);
    }
    fclose(shuff);

    keys = bams_array(bas, &bas_sz);

/*
    keys = bams_less(bas, "b", &bas_sz);
*/
    for (i = 0; i < bas_sz; i++) {
        printf("%s", keys[i]);
        free(keys[i]);
    }

    free(keys);
/*
    printf("Set size: %lu\n", bams_get_size(bas));
    printf("Check structure result: %d\n", bams_check_structure(bas));
*/
    
    bams_free(bas);
    /* qsort(&argv[1], argc-1, sizeof (char *), cmp_str);
    for (i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    */
    return 0;
}
