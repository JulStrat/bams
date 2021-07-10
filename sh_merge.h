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

/**
 * @file    sh_merge.h
 * @brief   Merge two sorted arrays.
 * @author  Ioulianos Kakoulidis
 */

/*
 * GNU indent program options: -orig -bad -bap -bs -cli2 -di1 -nbc -nut
 */

#ifndef SH_MERGE_H
#define SH_MERGE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @brief   Merge two sorted arrays.
 *
 * @param arr_a     First array
 * @param num_el_a  Number of elements in array arr_a
 * @param arr_b     Second array
 * @param num_el_b  Number of elements in array arr_b
 * @param el_size   Element size (in bytes)
 * @param compare   Compare function
 *
 * @return Resulting array or NULL
 *
 */
    void *merge(const void *arr_a, size_t num_el_a,
                const void *arr_b, size_t num_el_b,
                size_t el_size, int (*compare) (const void *,
                                                const void *));

/**
 *
 * @brief   Merge two sorted arrays.
 *          Reallocates dst array memory. Merge elements in reverse order.
 *
 * @param dst           Destination array
 * @param num_el_dst    Number of elements in array dst
 * @param src           Source array
 * @param num_el_src    Number of elements in array src
 * @param el_size       Element size (in bytes)
 * @param compare       Compare function
 *
 * @return Resulting array or NULL
 *
 */
    void *merge_into(void *dst, size_t num_el_dst,
                     const void *src, size_t num_el_src,
                     size_t el_size, int (*compare) (const void *,
                                                     const void *));

#ifdef __cplusplus
}
#endif
#ifdef SH_MERGE_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define ASSERT_MERGE_ARGS() \
    assert(el_size != 0); \
    assert(compare != NULL);
void *
merge(const void *arr_a, size_t num_el_a,
      const void *arr_b, size_t num_el_b,
      size_t el_size, int (*compare) (const void *, const void *))
{
    char *ac = (char *) arr_a;
    char *bc = (char *) arr_b;
    char *ah = ac + (num_el_a * el_size);
    char *bh = bc + (num_el_b * el_size);
    char *r = NULL;
    char *rc = NULL;

    ASSERT_MERGE_ARGS();

    r = (char *) malloc((num_el_a + num_el_b) * el_size);
    if (!r || !((num_el_a + num_el_b) * el_size)) {
        return NULL;
    }
    rc = r;

    while ((ac < ah) && (bc < bh)) {
        if ((*compare) (ac, bc) > 0) {
            memcpy(rc, bc, el_size);
            bc += el_size;
        } else {
            memcpy(rc, ac, el_size);
            ac += el_size;
        }
        rc += el_size;
    }

    if (ac < ah) {
        memcpy(rc, ac, ah - ac);
    } else if (bc < bh) {
        memcpy(rc, bc, bh - bc);
    }

    return r;
}

void *
merge_into(void *dst, size_t num_el_dst,
           const void *src, size_t num_el_src,
           size_t el_size, int (*compare) (const void *, const void *))
{
    char *dl;
    char *sl = (char *) src;
    char *dc;
    char *sc = sl + (num_el_src * el_size);
    char *r = NULL;
    char *rc = NULL;

    ASSERT_MERGE_ARGS();

    r = (char *) realloc(dst, (num_el_dst + num_el_src) * el_size);
    if (!r || !((num_el_dst + num_el_src) * el_size)) {
        return NULL;
    }
    rc = r + (num_el_dst + num_el_src) * el_size;

    dl = (char *) r;
    dc = dl + (num_el_dst * el_size);

    while ((dl < dc) && (sl < sc)) {
        if ((*compare) (dc - el_size, sc - el_size) > 0) {
            memcpy(rc - el_size, dc - el_size, el_size);
            dc -= el_size;
        } else {
            memcpy(rc - el_size, sc - el_size, el_size);
            sc -= el_size;
        }
        rc -= el_size;
    }

    if (sl < sc) {
        memcpy(r, sl, sc - sl);
    }

    return r;
}
#endif
#endif
