[![Build status](https://ci.appveyor.com/api/projects/status/github/JulStrat/bams?svg=true)](https://ci.appveyor.com/project/JulStrat/bams)
[![codecov.io](https://codecov.io/github/JulStrat/bams/coverage.svg?branch=master)](https://codecov.io/github/JulStrat/bams?branch=master)
![license](https://img.shields.io/github/license/JulStrat/bams)

# BAMS - binary array multi set

One of my favorite data structures, 
described in [Introduction to Algorithms](https://en.wikipedia.org/wiki/Introduction_to_Algorithms), 
chapter 17 "Amortized Analysis", problem 17-2 "Making binary search dynamic".

Internally ```bams``` implemented as linked list of sorted in ascending order arrays of data or pointers.

Name BAS - "binary array set" and Java, Python, C++, Rust implementations 
was made by [Nayuki](https://www.nayuki.io/page/binary-array-set).

Testing framework - [greatest](https://github.com/silentbicycle/greatest).

List of English words - [words_alpha.txt](https://github.com/dwyl/english-words).

## API
``` C
BAMS * bams_create(size_t key_size,
				  int (*compare) (const void *, const void *));

int bams_insert(BAMS *set, const void *key);

const void * bams_min(const BAMS *set);

const void * bams_max(const BAMS *set);

void * bams_array(const BAMS *set, size_t *key_num);

size_t bams_size(const BAMS *set);

void bams_clear(BAMS *set);

void bams_free(BAMS *set);

int bams_check_structure(const BAMS *set);	
```
Order statistic queries
``` C
size_t bams_count_less(const BAMS *set, const void *key);

size_t bams_count_equal(const BAMS *set, const void *key);

size_t bams_count_great(const BAMS *set, const void *key);

void * bams_less(const BAMS *set, const void *key, size_t *key_num);

void * bams_equal(const BAMS *set, const void *key, size_t *key_num);

void * bams_great(const BAMS *set, const void *key, size_t *key_num);
```

## Usage examples

### Inversion count
Solution to SPOJ problem [INVCNT](https://www.spoj.com/problems/INVCNT/)
``` C
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
```