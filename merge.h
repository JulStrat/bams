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
 * @file    merge.h
 * @brief   Merge two sorted arrays.
 * @author  Ioulianos Kakoulidis
 */

#ifndef MERGE_H
#define MERGE_H

#ifdef __cplusplus
extern "C" {
#endif

#if 0
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
void * merge(const void *arr_a, size_t num_el_a,
             const void *arr_b, size_t num_el_b,
             size_t el_size, int (*compare)(const void *, const void *));
#endif

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
void * merge_into(void *dst, size_t num_el_dst,
                  const void *src, size_t num_el_src,
                  size_t el_size, int (*compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif

#endif
