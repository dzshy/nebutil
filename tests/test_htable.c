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

    printf("[PASS] htable\n\n");
}

