/*
 * ISC License
 * 
 * Copyright (c) 2021, Ioulianos Kakoulidis
 * 
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR 
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE. 
 */

/*
 * indent options: -orig -nut -nbc -di1 
 */

/**
 * @file    bisect.c
 * @brief   Ordered array bisection algorithms.
 * @author  Ioulianos Kakoulidis
 */

#include <stddef.h>

void *
bisect_left(const void *key, const void *arr,
            size_t el_num, size_t el_size,
            int (*compare) (const void *, const void *))
{
    size_t low = 0;
    size_t high = el_num;
    size_t mid;
    char *off;

    while (low < high) {
        mid = low + ((high - low) >> 1);
        off = (char *) arr + mid * el_size;
        if ((*compare) (key, off) > 0) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return (char *) arr + low * el_size;
}

void *
bisect_right(const void *key, const void *arr,
             size_t el_num, size_t el_size,
             int (*compare) (const void *, const void *))
{
    size_t low = 0;
    size_t high = el_num;
    size_t mid;
    char *off;

    while (low < high) {
        mid = low + ((high - low) >> 1);
        off = (char *) arr + mid * el_size;
        if ((*compare) (key, off) < 0) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return (char *) arr + low * el_size;
}

#if 0
void *
bin_search(const void *key, const void *arr,
           size_t el_num, size_t el_size,
           int (*compare) (const void *, const void *))
{
    char *off = (char *) bisect_left(key, arr, el_num, el_size, compare);

    if ((off - (char *) arr) == el_num * el_size) {
        /*
         * At the ``end'' of array 
         */
        return NULL;
    }
    if ((*compare) (key, off) == 0) {
        return off;
    }
    return NULL;
}
#endif
