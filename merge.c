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

#include <stdlib.h>
#include <string.h>

void * merge(const void *a, const void *b,
             size_t len_a, size_t len_b,
             size_t key_size, int (*compare)(const void *, const void *))
{
    char *ac = (char *)a;
    char *bc = (char *)b;
    char *ah = ac + (len_a * key_size);
    char *bh = bc + (len_b * key_size);
    char *r = (char *)malloc((len_a + len_b) * key_size);
    char *rc = r;

    while ((ac < ah) && (bc < bh))
    {
        if ((*compare)(ac, bc) > 0)
        {
            memcpy(rc, bc, key_size);
            bc += key_size;
        }
        else
        {
            memcpy(rc, ac, key_size);
            ac += key_size;
        }
        rc += key_size;
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
