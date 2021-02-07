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

#ifndef BAMS_H
#define BAMS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _BAMS BAMS;

BAMS * bams_create(size_t key_size,
                   int (*compare)(const void *, const void *));

int bams_contains(const BAMS *set, const void *key);

int bams_insert(BAMS *set, const void *key);

/*
size_t bams_count_less(const void *set, const void *key);
size_t bams_count_equal(const void *set, const void *key);
size_t bams_count_great(const void *set, const void *key);
void * bams_less(const void *set, const void *key, size_t *key_num);
void * bams_equal(const void *set, const void *key, size_t *key_num);
void * bams_great(const void *set, const void *key, size_t *key_num);
void * bams_array(const void *set, size_t *key_num);
*/

size_t bams_get_size(const BAMS *set);

void bams_free(BAMS *set);

int bams_check_structure(BAMS *set);

#ifdef __cplusplus
}
#endif

#endif