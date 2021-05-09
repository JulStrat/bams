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
 * @file    bams.c
 * @brief   Binary Array MultiSet C API implementation.
 *          Implementation of the functions declared in the C header 
 *          file bams.h
 * @author  Ioulianos Kakoulidis
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bams.h"
#include "merge.h"
#include "bisect.h"

#define SLOTS_NUM (sizeof (size_t)) * 8
#define LENGTH(x) ((set->slots)[(x)] ? 1 << (x): 0)

/** BAMS structure */
struct _BAMS
{
    /** Key size in bytes */
    size_t key_size;
    /** Compare function */
    int (*compare)(const void *, const void *);
    
    void *slots[SLOTS_NUM];
    /** Set cardinality (number of keys) */
    size_t size;
};

BAMS * bams_create(size_t key_size,
                   int (*compare)(const void *, const void *))
{
    BAMS *set = (BAMS *)malloc(sizeof (BAMS));
    size_t i;
    
    if (NULL != set) {
        set->key_size = key_size;
        set->compare = compare;
        set->size = 0;
        for (i = 0; i < SLOTS_NUM; i++) {
            set->slots[i] = NULL;
        }
    }

    return set;
}

int bams_contains(const BAMS *set, const void *key)
{
    size_t i;
    void *key_pos;

    for (i = 0; i < SLOTS_NUM; i++) {
        key_pos = bin_search(key, (set->slots)[i], LENGTH(i),
                             set->key_size, set->compare);
        if (NULL != key_pos) {
            return 1;
        }
    }

    return 0;
}

int bams_insert(BAMS *set, const void *key)
{
    size_t i, length = 1;
    void *keys;
    void *t;

    keys = malloc(set->key_size);
    memcpy(keys, key, set->key_size);

    for (i = 0; i < SLOTS_NUM; i++) {    
        if ((set->slots)[i])
        {
            t = merge_into(keys, LENGTH(i), (set->slots)[i], LENGTH(i),
                      set->key_size, set->compare);
            keys = t;            
            free((set->slots)[i]);
            (set->slots)[i] = NULL;
        }
        else {
            (set->slots)[i] = keys;
            set->size += 1;
            return 1;
        }
    }
    
    return 0;
}

/*
void * bams_min(const BAMS *set)
{
    size_t i, length = 1;    
    void *min_key = NULL;

    if (set->size > 0)
    {
        min_key = curr->keys;
        while (NULL != curr->next)
        {
            curr = curr->next;
            if ((*(set->compare))(min_key, curr->keys) > 0)
            {
                min_key = curr->keys;
            }
        }
        for (i = 0; i < SLOTS_NUM; i++) {
        	length += length;
	    }
        
    }
    

    return min_key;
}

void * bams_max(const BAMS *set)
{
    size_t i, length = 1;        
    size_t key_size = set->key_size;
    char *last = NULL;
    char *max_key = NULL;

    if (set->size > 0)
    {
        max_key = (char *)curr->keys + (curr->length - 1) * key_size;
        while (NULL != curr->next)
        {
            curr = curr->next;
            last = (char *)curr->keys + (curr->length - 1) * key_size;
            if ((*(set->compare))(last, max_key) > 0)
            {
                max_key = last;
            }
        }
    }

    return max_key;
}
*/
size_t bams_count_less(const BAMS *set, const void *key)
{
    size_t i;        
    size_t key_size = set->key_size;
    char *off;
    size_t less = 0;

    for (i = 0; i < SLOTS_NUM; i++) {    
        off = (char *)bisect_left(key, (set->slots)[i], LENGTH(i),
                                  key_size, set->compare);
        assert(off >= (char *)(set->slots)[i]);
        less += off - (char *)(set->slots)[i];
    }

    return (size_t)(less / key_size);
}

size_t bams_count_equal(const BAMS *set, const void *key)
{
    size_t i;        
    size_t key_size = set->key_size;
    char *low;
    char *high;
    size_t equal = 0;

    for (i = 0; i < SLOTS_NUM; i++) {    
        low = (char *)bisect_left(key, (set->slots)[i], LENGTH(i),
                                  key_size, set->compare);
        high = (char *)bisect_right(key, (set->slots)[i], LENGTH(i),
                                    key_size, set->compare);
        assert(high >= low);
        equal += high - low;
    }

    return (size_t)(equal / key_size);
}

size_t bams_count_great(const BAMS *set, const void *key)
{
    size_t i;        
    size_t key_size = set->key_size;
    char *low;
    char *high;
    size_t great = 0;

    for (i = 0; i < SLOTS_NUM; i++) {    
        low = (char *)bisect_right(key, (set->slots)[i], LENGTH(i),
                                   key_size, set->compare);
        high = (char *)(set->slots)[i] + LENGTH(i) * key_size;
        assert(high >= low);
        great += high - low;
    }

    return (size_t)(great / key_size);
}

void * bams_less(const BAMS *set, const void *key, size_t *key_num)
{
    size_t i;        
    size_t key_size = set->key_size;
    char *off;
    char *r = NULL;
    char *t;
    size_t less = 0;

    *key_num = 0;
    for (i = 0; i < SLOTS_NUM; i++) {    
        off = (char *)bisect_left(key, (set->slots)[i], LENGTH(i),
                                  key_size, set->compare);
        assert(off >= (char *)(set->slots)[i]);
        less = (size_t)((off - (char *)(set->slots)[i]) / key_size);
        if (less > 0)
        {
            t = merge_into(r, *key_num, (set->slots)[i], less,
                           key_size, set->compare);
            /* free(r); */
            r = t;
            *key_num += less;
        }
    }

    return r;
}

void * bams_equal(const BAMS *set, const void *key, size_t *key_num)
{
    size_t i;        
    size_t key_size = set->key_size;
    char *low;
    char *high;
    char *r = NULL;
    size_t equal = 0;

    *key_num = 0;

    for (i = 0; i < SLOTS_NUM; i++) {    
        low = (char *)bisect_left(key, (set->slots)[i], LENGTH(i),
                                  key_size, set->compare);
        high = (char *)bisect_right(key, (set->slots)[i], LENGTH(i),
                                    key_size, set->compare);
        assert(high >= low);
        if (high > low)
        {
            r = realloc(r, equal + high - low);
            assert (NULL != r);
            memcpy(r + equal, low, high - low);
            equal += high - low;
        }
    }

    *key_num = (size_t)(equal / key_size);

    return r;
}

void * bams_great(const BAMS *set, const void *key, size_t *key_num)
{
    size_t i;        
    size_t key_size = set->key_size;
    char *low;
    char *high;
    char *r = NULL;
    char *t;
    size_t great = 0;

    *key_num = 0;

    for (i = 0; i < SLOTS_NUM; i++) {    
        low = (char *)bisect_right(key, (set->slots)[i], LENGTH(i),
                                   key_size, set->compare);
        high = (char *)(set->slots)[i] + LENGTH(i) * key_size;
        assert(high >= low);
        great = (size_t)((high - low) / key_size);
        if (great > 0)
        {
            t = merge_into(r, *key_num, low, great,
                           key_size, set->compare);
            /* free(r); */
            r = t;
            *key_num += great;
        }
    }

    return r;
}

void * bams_array(const BAMS *set, size_t *key_num)
{
    size_t i;        
    char *r = NULL;
    char *t;
    
    *key_num = 0;
    for (i = 0; i < SLOTS_NUM; i++) {
        if ((set->slots)[i]) {
            t = merge_into(r, *key_num, (set->slots)[i], LENGTH(i),
                           set->key_size, set->compare);
            r = t;
            *key_num += LENGTH(i);
        }        
    }

    return r;
}

size_t bams_get_size(const BAMS *set)
{
    return set->size;
}

void bams_clear(BAMS *set)
{
    size_t i;        

    for (i = 0; i < SLOTS_NUM; i++) {    
        free((set->slots)[i]);
        (set->slots)[i] = NULL;
    }
    set->size = 0;
}

void bams_free(BAMS *set)
{
    size_t i;        

    for (i = 0; i < SLOTS_NUM; i++) {    
        free((set->slots)[i]);
        (set->slots)[i] = NULL;
    }
    set->size = 0;
    free(set);
    set = NULL;
}

int bams_check_structure(const BAMS *set)
{
    char *off;

    size_t set_size = 0;
    size_t key_size = set->key_size;
    size_t length;
    size_t i;        

    for (i = 0; i < SLOTS_NUM; i++) {
        length = LENGTH(i);
        set_size += LENGTH(i);
        off = (char *)(set->slots)[i];
        /* check ascending */
        while (length-- > 1) {
            if ((set->compare)(off, off + key_size) > 0) {
                return 1;
            }
            off += key_size;
        }
    }
	
    if (set_size != set->size) {
        return 2;
    }

    return 0;
}

