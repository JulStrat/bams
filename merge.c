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
 * @file   merge.c
 * @brief  Merge two sorted arrays.
 * @author Ioulianos Kakoulidis
 */

#include <stdlib.h>
#include <string.h>

void * merge(const void *arr_a, size_t num_el_a,
             const void *arr_b, size_t num_el_b,
             size_t el_size, int (*compare)(const void *, const void *))
{
    char *ac = (char *)arr_a;
    char *bc = (char *)arr_b;
    char *ah = ac + (num_el_a * el_size);
    char *bh = bc + (num_el_b * el_size);
    char *r = (char *)malloc((num_el_a + num_el_b) * el_size);
    char *rc = r;

    while ((ac < ah) && (bc < bh))
    {
        if ((*compare)(ac, bc) > 0)
        {
            memcpy(rc, bc, el_size);
            bc += el_size;
        }
        else
        {
            memcpy(rc, ac, el_size);
            ac += el_size;
        }
        rc += el_size;
    }

    if (ac < ah)
    {
        memcpy(rc, ac, ah - ac);
    } 
    else if (bc < bh)
    {
        memcpy(rc, bc, bh - bc);
    }

    return r;
}
