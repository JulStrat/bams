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

/** Linked list of BAMS nodes */
struct _SET_NODE {
    /** Next node */
    struct _SET_NODE *next;
    /** Array length (number of elements) */
    size_t length;
    /** Sorted (ascending) array of keys */
    void *keys;
};

typedef struct _SET_NODE SET_NODE;
typedef enum {COPY_POINTER = 0, COPY_DATA} BAMS_TYPE;

/** BAMS structure */
struct _BAMS {
    /** Key size in bytes */
    size_t key_size;
    /** Compare function */
    int (*compare) (const void *, const void *);
    /** BAMS first node */
    SET_NODE *head;
    /** Set cardinality (number of keys) */
    size_t size;
    BAMS_TYPE type;    
};

static SET_NODE *make_node(const BAMS * set, void *key);

BAMS *
bams_create(size_t key_size, int (*compare) (const void *, const void *))
{
    BAMS *set = (BAMS *) malloc(sizeof(BAMS));

    if (!set) {
        return NULL;
    }

    if (key_size) {
        set->key_size = key_size;
        set->type = COPY_DATA;
    }
    else {
        set->key_size = sizeof (void *);
        set->type = COPY_POINTER;
    }
    set->compare = compare;
    set->head = NULL;
    set->size = 0;

    return set;
}

#if 0
int
bams_contains(const BAMS * set, const void *key)
{
    SET_NODE *curr = set->head;
    void *key_pos;

    while (NULL != curr) {
        key_pos = bin_search(key, curr->keys, curr->length,
                             set->key_size, set->compare);
        if (NULL != key_pos) {
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}
#endif

int
bams_insert(BAMS * set, const void *key)
{
    SET_NODE *curr = set->head;
    void *keys;
    void *t;
    size_t length = 1;
    SET_NODE *node;
    SET_NODE *next;

    node = make_node(set, key);
    if (!node) {
        return 0;
    }

    node->next = curr;
    set->head = node;
    set->size += 1;

    /*
     * Normalize 
     */
    while (curr != NULL) {
        if ((node->length) >= (curr->length)) {
            next = curr->next;

            t = merge_into(curr->keys, curr->length, node->keys,
                           node->length, set->key_size, set->compare);
            if (NULL == t) {
                return 1;       /* return norm error ! */
            }
            curr->keys = t;
            curr->length += node->length;
            set->head = curr;

            /* free node */
            free(node->keys);
            free(node);

            node = curr;
            curr = next;
        } else
            break;
    }
    return 1;
}

void *
bams_min(const BAMS * set)
{
    SET_NODE *curr = set->head;
    void *min_key = NULL;

    if (set->size > 0) {
        min_key = curr->keys;
        while (NULL != curr->next) {
            curr = curr->next;
            if ((*(set->compare)) (min_key, curr->keys) > 0) {
                min_key = curr->keys;
            }
        }
    }

    return min_key;
}

void *
bams_max(const BAMS * set)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *last = NULL;
    char *max_key = NULL;

    if (set->size > 0) {
        max_key = (char *) curr->keys + (curr->length - 1) * key_size;
        while (NULL != curr->next) {
            curr = curr->next;
            last = (char *) curr->keys + (curr->length - 1) * key_size;
            if ((*(set->compare)) (last, max_key) > 0) {
                max_key = last;
            }
        }
    }

    return max_key;
}

size_t
bams_count_less(const BAMS * set, const void *key)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *off;
    size_t less = 0;

    while (NULL != curr) {
        off = (char *) bisect_left(key, curr->keys, curr->length,
                                   key_size, set->compare);
        assert(off >= (char *) curr->keys);
        less += off - (char *) curr->keys;
        curr = curr->next;
    }

    return (size_t) (less / key_size);
}

size_t
bams_count_equal(const BAMS * set, const void *key)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *low, *high;
    size_t equal = 0;

    while (NULL != curr) {
        low = (char *) bisect_left(key, curr->keys, curr->length,
                                   key_size, set->compare);
        high = (char *) bisect_right(key, curr->keys, curr->length,
                                     key_size, set->compare);
        assert(high >= low);
        equal += high - low;
        curr = curr->next;
    }

    return (size_t) (equal / key_size);
}

size_t
bams_count_great(const BAMS * set, const void *key)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *low, *high;
    size_t great = 0;

    while (NULL != curr) {
        low = (char *) bisect_right(key, curr->keys, curr->length,
                                    key_size, set->compare);
        high = (char *) curr->keys + curr->length * key_size;
        assert(high >= low);
        great += high - low;
        curr = curr->next;
    }

    return (size_t) (great / key_size);
}

void *
bams_less(const BAMS * set, const void *key, size_t * key_num)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *off;
    char *r = NULL;
    char *t;
    size_t less = 0;

    *key_num = 0;
    while (NULL != curr) {
        off = (char *) bisect_left(key, curr->keys, curr->length,
                                   key_size, set->compare);
        assert(off >= (char *) curr->keys);
        less = (size_t) ((off - (char *) curr->keys) / key_size);
        if (less > 0) {
            t = merge_into(r, *key_num, curr->keys, less,
                           key_size, set->compare);
            /*
             * free(r); 
             */
            r = t;
            *key_num += less;
        }
        curr = curr->next;
    }

    return r;
}

void *
bams_equal(const BAMS * set, const void *key, size_t * key_num)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *low, *high;
    char *r = NULL;
    size_t equal = 0;

    *key_num = 0;
    while (NULL != curr) {
        low = (char *) bisect_left(key, curr->keys, curr->length,
                                   key_size, set->compare);
        high = (char *) bisect_right(key, curr->keys, curr->length,
                                     key_size, set->compare);
        assert(high >= low);
        if (high > low) {
            r = realloc(r, equal + high - low);
            assert(NULL != r);
            memcpy(r + equal, low, high - low);
            equal += high - low;
        }

        curr = curr->next;
    }
    *key_num = (size_t) (equal / key_size);

    return r;
}

void *
bams_great(const BAMS * set, const void *key, size_t * key_num)
{
    SET_NODE *curr = set->head;
    size_t key_size = set->key_size;
    char *low, *high;
    char *r = NULL;
    char *t;
    size_t great = 0;

    *key_num = 0;
    while (NULL != curr) {
        low = (char *) bisect_right(key, curr->keys, curr->length,
                                    key_size, set->compare);
        high = (char *) curr->keys + curr->length * key_size;
        assert(high >= low);
        great = (size_t) ((high - low) / key_size);
        if (great > 0) {
            t = merge_into(r, *key_num, low, great,
                           key_size, set->compare);
            /*
             * free(r); 
             */
            r = t;
            *key_num += great;
        }
        curr = curr->next;
    }

    return r;
}

void *
bams_array(const BAMS * set, size_t * key_num)
{
    SET_NODE *curr = set->head;
    char *r = NULL;
    char *t;

    *key_num = 0;
    while (NULL != curr) {
        t = merge_into(r, *key_num, curr->keys, curr->length,
                       set->key_size, set->compare);
        /*
         * free(r); 
         */
        r = t;
        *key_num += curr->length;
        curr = curr->next;
    }

    return r;
}

size_t
bams_get_size(const BAMS * set)
{
    return set->size;
}

void
bams_clear(BAMS * set)
{
    SET_NODE *curr = set->head;
    SET_NODE *next;

    while (NULL != curr) {
        next = curr->next;
        free(curr->keys);
        free(curr);
        curr = next;
    }
    set->head = NULL;
    set->size = 0;
}

void
bams_free(BAMS * set)
{
    SET_NODE *curr = set->head;
    SET_NODE *next;

    while (NULL != curr) {
        next = curr->next;
        free(curr->keys);
        free(curr);
        curr = next;
    }
    free(set);
}

int
bams_check_structure(const BAMS * set)
{
    SET_NODE *curr = set->head;
    char *off;

    size_t set_size = 0;
    size_t node_len = 0;
    size_t key_size = set->key_size;

    while (NULL != curr) {
        if ((node_len >= curr->length) || (0 == curr->length)) {
            return 1;
        }
        /*
         * check if node length is power of two 
         */
        node_len = curr->length;
        /*
         * printf("node len: %d\n", node_len); 
         */
        while (0 == (node_len & 1)) {
            node_len >>= 1;
        }
        if (node_len > 1) {
            return 2;
        }
        node_len = curr->length;
        set_size += node_len;

        /*
         * check current node keys 
         */
        off = (char *) (curr->keys);
        while (node_len-- > 1) {
            if ((set->compare) (off, off + key_size) > 0) {
                return 3;
            }
            off += key_size;
        }

        curr = curr->next;
    }
    if (set_size != set->size) {
        return 4;
    }
    return 0;
}

/*
 * Internal functions 
 */

static SET_NODE *
make_node(const BAMS * set, void *key)
{
    SET_NODE *node = (SET_NODE *) malloc(sizeof(SET_NODE));
    void *keys;
    
    if (!node) {
        return NULL;
    }

    keys = malloc(set->key_size);
    if (!keys) {
        free(node);
        return NULL;
    }

    switch (set->type) {
        case COPY_DATA:
            memcpy(keys, key, set->key_size);
            break;
        default:
            *(void **)keys = key;
            break;
    }
    node->keys = keys;
    node->length = 1;

    return node;
}
