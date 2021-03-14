#include <stdio.h>
#include "bams.h"

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

int
main(int argc, char *argv[])
{
    int a, tc, n;
    unsigned long inv;
    BAMS *bas;

    bas = bams_create(sizeof(int), cmp_int);
    scanf("%d", &tc);
    while (tc--) {
        inv = 0;
        scanf("%d", &n);
        while (n--) {
            scanf("%d", &a);
            inv += bams_count_great(bas, &a);
            bams_insert(bas, &a);
        }
        printf("%lu\n", inv);
        bams_clear(bas);
    }

    bams_free(bas);

    return 0;
}
