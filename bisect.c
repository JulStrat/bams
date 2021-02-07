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

#include <stddef.h>

void * bisect_left(const void *key, const void *a, 
                   size_t len, size_t key_size,
                   int (*compare)(const void *, const void *))
{
    size_t low = 0;
    size_t high = len;
    size_t mid;
    int t;
    char *off = NULL;
    
    while (low < high)
    {
        mid = low + ((high - low) >> 1);
        off = (char *)a + mid * key_size;
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

    return (char *)a + low * key_size;;
}

void * bin_search(const void *key, const void *base,
                  size_t elnum, size_t elsize,
                  int (*compare) (const void *, const void *))
{
    char *off = (char *)bisect_left(key, base, elnum, elsize, compare);

    if ((off - (char *)base) == elnum * elsize)
    {
        return NULL;
    }
    if (0 == (*compare)(key, off))
    {
        return off;
    }
    return NULL;
}


/*
void * bisect_right(const void *a, const void *key,
                   size_t len, size_t key_size,
                   int (*compare)(const void *, const void *))
{
}
*/
