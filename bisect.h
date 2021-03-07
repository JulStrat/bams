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
 * @file    bisect.h
 * @brief   Python like array bisection algorithms.
 *          Binary search algorithm.
 * @author  Ioulianos Kakoulidis
 */

#ifndef BISECT_H
#define BISECT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Find position of the first element equal or great
 *          than given key in sorted in ascending order array. 
 *          If not found, return ``end'' of array.
 *
 * @param key       Bisection key
 * @param arr       Array
 * @param el_num    Elements number
 * @param el_size   Element size
 * @param compare   Compare function
 *
 */
    void *bisect_left(const void *key, const void *arr,
                      size_t el_num, size_t el_size,
                      int (*compare) (const void *, const void *));

/**
 * @brief   Find position of the first element great
 *          than given key in sorted in ascending order array. 
 *          If not found, return ``end'' of array.
 *
 * @param key       Bisection key
 * @param arr       Array
 * @param el_num    Elements number
 * @param el_size   Element size
 * @param compare   Compare function
 *
 */
    void *bisect_right(const void *key, const void *arr,
                       size_t el_num, size_t el_size,
                       int (*compare) (const void *, const void *));

/**
 * @brief   Find position of the first element equal 
 *          to given key in sorted in ascending order array. 
 *          If not found, return NULL.
 *
 * @param key       Key to find
 * @param arr       Array
 * @param el_num    Elements number
 * @param el_size   Element size
 * @param compare   Compare function
 *
 */
    void *bin_search(const void *key, const void *arr,
                     size_t el_num, size_t el_size,
                     int (*compare) (const void *, const void *));

#ifdef __cplusplus
}
#endif
#endif
