/*
ISC License

Copyright (c) 2021, Ioulianos Kakoulidis

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/**
 * @file bisect.c
 * @brief Array bisection functions.
 * @author Ioulianos Kakoulidis
 */

#include <stddef.h>

void * bisect_left(const void *key, const void *arr,
                   size_t el_num, size_t el_size,
                   int (*compare)(const void *, const void *))
{
    size_t low = 0;
    size_t high = el_num;
    size_t mid;
    int t;
    char *off = NULL;
    
    while (low < high)
    {
        mid = low + ((high - low) >> 1);
        off = (char *)arr + mid * el_size;
        t = (*compare)(key, off);
        if (t > 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }

    return (char *)arr + low * el_size;
}

void * bisect_right(const void *key, const void *arr,
                   size_t el_num, size_t el_size,
                   int (*compare)(const void *, const void *))
{
    size_t low = 0;
    size_t high = el_num;
    size_t mid;
    int t;
    char *off = NULL;
    
    while (low < high)
    {
        mid = low + ((high - low) >> 1);
        off = (char *)arr + mid * el_size;
        t = (*compare)(key, off);
        if (t < 0)
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    return (char *)arr + low * el_size;
}

void * bin_search(const void *key, const void *arr,
                  size_t el_num, size_t el_size,
                  int (*compare)(const void *, const void *))
{
    char *off = (char *)bisect_left(key, arr, el_num, el_size, compare);

    if ((off - (char *)arr) == el_num * el_size)
    {
        return NULL;
    }
    if (0 == (*compare)(key, off))
    {
        return off;
    }
    return NULL;
}
