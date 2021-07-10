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
 * @file   bams.h
 * @brief  Binary Array MultiSet C API.
 * @author Ioulianos Kakoulidis
 */

#ifndef BAMS_H
#define BAMS_H

#define BAMS_VERSION "0.2.0"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _BAMS BAMS;

/**
 * @brief Create BAM set.
 *
 * @param key_size    Key size      
 * @param compare     Compare function
 *
 */
    BAMS *bams_create(size_t key_size,
                      int (*compare) (const void *, const void *));


#if 0
/**
 * @brief      Check if set contains given key
 * @deprecated Use @ref bams_count_equal
 */
    int bams_contains(const BAMS * set, const void *key);
#endif

/**
 * @brief Insert key into set.
 *
 *
 *   
 *
 */
    int bams_insert(BAMS * set, const void *key);

/**
 * @brief Return minimum key of the set.
 *
 * @return min such that compare(min, key) <= 0 for any key from the set
 *         if set is empty - return NULL  
 */
    void *bams_min(const BAMS * set);

/**
 * @brief Return maximum key of the set.
 *
 * @return max such that compare(max, key) >= 0 for any key from the set
 *         if set is empty - return NULL  
 */
    void *bams_max(const BAMS * set);

/**
 * @brief Count number of keys less than given.  
 *
 *
 *   
 *
 */
    size_t bams_count_less(const BAMS * set, const void *key);

/**
 * @brief Count number of keys equal to given.  
 *
 *
 *   
 *
 */
    size_t bams_count_equal(const BAMS * set, const void *key);

/**
 * @brief Count number of keys great than given.  
 *
 *
 *   
 *
 */
    size_t bams_count_great(const BAMS * set, const void *key);

/**
 * @brief Return ordered array of keys lass than given.  
 *
 *
 *   
 *
 */
    void *bams_less(const BAMS * set, const void *key, size_t *key_num);

/**
 * @brief Return array of keys equal to given.  
 *
 *
 *   
 *
 */
    void *bams_equal(const BAMS * set, const void *key, size_t *key_num);

/**
 * @brief Return ordered array of keys great than given.  
 *
 *
 *   
 *
 */
    void *bams_great(const BAMS * set, const void *key, size_t *key_num);


/**
 * @brief Return ordered array of keys.  
 *
 *
 *   
 *
 */
    void *bams_array(const BAMS * set, size_t *key_num);

/**
 * @brief Returns number of keys.
 *
 *
 *   
 *
 */
    size_t bams_get_size(const BAMS * set);

/**
 * @brief Remove all keys from set.
 *
 *
 *   
 *
 */
    void bams_clear(BAMS * set);

/**
 * @brief Destroy set.
 *
 *
 *   
 *
 */
    void bams_free(BAMS * set);

/**
 * @brief Check set internal structure.
 *
 *
 *   
 *
 */
    int bams_check_structure(const BAMS * set);

#ifdef __cplusplus
}
#endif
#endif
