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
    char **lt_keys = NULL, **eq_keys = NULL, **gt_keys = NULL;
    size_t bas_sz = 0;
    int i;
    FILE *shuff;
    char bf[1024];
    char *key;
    size_t lt_num = 0, eq_num = 0, gt_num = 0;

    shuff = fopen(argv[1], "r");
    bas = bams_create(0, cmp_str);

    while (fgets(bf, 1024, shuff)) {
        key = malloc(strlen(bf) + 1);
        strcpy(key, bf);
        bams_insert(bas, key);
    }
    fclose(shuff);

    lt_keys = bams_less(bas, "obelisk", &lt_num);
    assert(lt_num == bams_count_less(bas, "obelisk"));

    eq_keys = bams_equal(bas, "obelisk", &eq_num);
    assert(eq_num == bams_count_equal(bas, "obelisk"));

    gt_keys = bams_great(bas, "obelisk", &gt_num);
    assert(gt_num == bams_count_great(bas, "obelisk"));

    assert(bams_get_size(bas) == (lt_num + eq_num + gt_num));

    for (i = 0; i < lt_num; i++) {
        printf("%s", lt_keys[i]);
        free(lt_keys[i]);
    }

    for (i = 0; i < eq_num; i++) {
        printf("%s", eq_keys[i]);
        free(eq_keys[i]);
    }

    for (i = 0; i < gt_num; i++) {
        printf("%s", gt_keys[i]);
        free(gt_keys[i]);
    }

    free(lt_keys);
    free(eq_keys);
    free(gt_keys);

    /*
     * keys = bams_array(bas, &bas_sz); 
     */

    /*
     * keys = bams_less(bas, "b", &bas_sz); 
     */

    /*
     * for (i = 0; i < bas_sz; i++) { printf("%s", keys[i]); free(keys[i]); }
     * 
     * free(keys); 
     */

    /*
     * printf("Set size: %lu\n", bams_get_size(bas)); printf("Check structure 
     * result: %d\n", bams_check_structure(bas)); 
     */

    bams_free(bas);
    /*
     * qsort(&argv[1], argc-1, sizeof (char *), cmp_str); for (i = 1; i <
     * argc; i++) { printf("%s\n", argv[i]); } 
     */
    return 0;
}
