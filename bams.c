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
 * @file bams.c
 * @brief Binary Array MultiSet C API implementation.
 * Implementation of the functions declared in the C header file bams.h
 * @author Ioulianos Kakoulidis
 */

#include <stdlib.h>
#include <string.h>

#include "bams.h"
#include "merge.h"
#include "bisect.h"

struct _SET_NODE
{
    struct _SET_NODE *next;
    size_t length;
    /* sorted array of keys */
    void *keys;
};

typedef struct _SET_NODE SET_NODE;

struct _BAMS
{
    size_t key_size;
    int (*compare)(const void *, const void *);
    SET_NODE *head;
    size_t size;
};

static inline SET_NODE * create_node(void *keys, size_t length);
static inline void free_node(SET_NODE *node);

BAMS * bams_create(size_t key_size,
                   int (*compare)(const void *, const void *))
{
    BAMS *set = (BAMS *)malloc(sizeof (BAMS));

    if (NULL != set)
    {
        set->key_size = key_size;
        set->compare = compare;
        set->head = NULL;
        set->size = 0;
    }

    return set;
}

int bams_contains(const BAMS *set, const void *key)
{
    SET_NODE *curr = set->head;
    void *key_pos;

    while (NULL != curr)
    {
        key_pos = bin_search(
                      key,
                      curr->keys,
                      curr->length,
                      set->key_size,
                      set->compare);
        if (NULL != key_pos)
        {
            return 1;
        }
        curr = curr->next;
    }

    return 0;
}

int bams_insert(BAMS *set, const void *key)
{
    SET_NODE *curr = set->head;
    void *keys;
    void *t;
    size_t length = 1;
    SET_NODE *node;
    SET_NODE *next;

    keys = malloc(length * (set->key_size));
    memcpy(keys, key, (set->key_size) * length);

    while (curr != NULL)
    {
        if (length == (curr->length))
        {
            next = curr->next;
            t = merge(keys, length, curr->keys, length,
                      set->key_size, set->compare);
            length *= 2;
            free(keys);
            free_node(curr);
            curr = next;
            keys = t;
        }
        else
            break;
    }
    node = create_node(keys, length);
    node->next = curr;
    set->head = node;
    set->size += 1;
    return 1;
}

void * bams_min(const BAMS *set)
{
    void *min_key = NULL;
    SET_NODE *curr = set->head;

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
    }

    return min_key;
}

void * bams_max(const BAMS *set)
{
    char *max_key = NULL;
    SET_NODE *curr = set->head;
    char *last = NULL;

    if (set->size > 0)
    {
        max_key = (char *)curr->keys + (curr->length - 1) * set->key_size;
        while (NULL != curr->next)
        {
            curr = curr->next;
            last = (char *)curr->keys + (curr->length - 1) * set->key_size;
            if ((*(set->compare))(last, max_key) > 0)
            {
                max_key = last;
            }
        }
    }

    return max_key;
}

size_t bams_count_less(const BAMS *set, const void *key)
{
    SET_NODE *curr = set->head;
    char *off;
    size_t less = 0;

    while (NULL != curr)
    {
        off = (char *)bisect_left(key, curr->keys, curr->length,
                                  set->key_size, set->compare);
        less += off - (char *)curr->keys;
        curr = curr->next;
    }

    return (size_t) less / set->key_size;
}

size_t bams_get_size(const BAMS *set)
{
    return set->size;
}

void bams_clear(BAMS *set)
{
    SET_NODE *curr = set->head;
    SET_NODE *next;

    while (NULL != curr)
    {
        next = curr->next;
        free(curr->keys);
        free(curr);
        curr = next;
    }
    set->head = NULL;
    set->size = 0;
}

void bams_free(BAMS *set)
{
    SET_NODE *curr = set->head;
    SET_NODE *next;

    while (NULL != curr)
    {
        next = curr->next;
        free(curr->keys);
        free(curr);
        curr = next;
    }
    free(set);
}

int bams_check_structure(const BAMS *set)
{
    SET_NODE *curr = set->head;
    char *off;

    size_t set_size = 0;
    size_t node_len = 0;
    size_t key_size = set->key_size;

    while (NULL != curr)
    {
        if ((node_len >= curr->length) || (0 == curr->length))
        {
            return 1;
        }
        /* check if node length is power of two */
        node_len = curr->length;
        //printf("node len: %d\n", node_len);
        while (0 == (node_len & 1))
        {
            node_len >>= 1;
        }
        if (node_len > 1)
        {
            return 2;
        }
        node_len = curr->length;
        set_size += node_len;

        /* check current node keys */
        off = (char *)(curr->keys);
        while (node_len-- > 1)
        {
            if ((set->compare)(off, off + key_size) > 0)
            {
                return 3;
            }
            off += key_size;
        }

        curr = curr->next;
    }
    if (set_size != set->size)
    {
        return 4;
    }
    return 0;
}

/* Internal functions */
static inline SET_NODE * create_node(void *keys, size_t length)
{
    SET_NODE *node = (SET_NODE *)malloc(sizeof (SET_NODE));

    if (NULL != node)
    {
        node->keys = keys;
        node->length = length;
    }

    return node;
}

static inline void free_node(SET_NODE *node)
{
    if (NULL != node)
    {
       free(node->keys);
    }
    free(node);
}
