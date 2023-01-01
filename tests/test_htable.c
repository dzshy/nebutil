/* Copyright (c) 2022-2023, Dzshy <dzshy@outlook.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "crc32.h"
#include "htable.h"

static uint32_t hash(void *i) {
    return crc32(0, i, sizeof(int));
}

static bool eq(void *x, void *y) {
    int *a = x, *b = y;
    return *a == *b;
}

bool found[10000];

int main() {
    printf("[TEST] htable\n");
    
    HTable ht;
    htable_init(&ht, sizeof(int), -1, hash, eq);
    for (int i = 0; i < 10000; i++) {
        htable_insert(&ht, &i);
        assert(ht.size == i + 1);
        assert(ht.taken == i + 1);
        assert(ht.cap >= i + 1);
    }

    for (int i = 0; i < 10000; i++) {
        assert(htable_find(&ht, &i) != NULL); 
        int t = 10000 + i;
        assert(htable_find(&ht, &t) == NULL); 
    }

    memset(found, 0, sizeof(bool) * 10000);
    int *iter = htable_begin(&ht);
    while (iter != NULL) {
        found[*iter] = true;
        iter = htable_next(&ht, iter);
    }
    for (int i = 0; i < 10000; i++) {
        assert(found[i]);
    }
    
    for (int i = 0; i < 5000; i++) {
        int *iter = htable_find(&ht, &i);
        htable_del(&ht, iter);
    }
    for (int i = 0; i < 5000; i++) {
        assert(htable_find(&ht, &i) == NULL); 
        int t = 5000 + i;
        assert(htable_find(&ht, &t) != NULL); 
    }
    
    for (int i = 0; i < 5000; i++) {
        htable_insert(&ht, &i);
    }
    
    memset(found, 0, sizeof(bool) * 10000);
    iter = htable_begin(&ht);
    while (iter != NULL) {
        found[*iter] = true;
        iter = htable_next(&ht, iter);
    }
    for (int i = 0; i < 10000; i++) {
        assert(found[i]);
    }

    printf("[PASS] htable\n");
}

