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

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "rbtree.h"

typedef struct {
    RbNode node;
    int key;
    int value;
} IntIntEntry;

static int cmpfunc(void *x, void *y) {
    int *a = x, *b = y;
    return *a < *b ?  -1 : *a > *b;
}

static void test_largedata();

static int max(int a, int b) {
    return a > b ? a : b;
}

int depth(void *n) {
    RbNode *node = n;
    if (node == NULL) return 0;
    return max(depth(node->entry.rbe_left), depth(node->entry.rbe_right)) + 1;
}

int main() {
    printf("[TEST] rbtree\n");
    RbTree tree = {NULL, cmpfunc, NULL};
    IntIntEntry *n;

    int a[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i ++) {
        n = malloc(sizeof(*n));
        n->key = a[i];
        n->value = i;
        rbtree_insert(&tree, n);
    }

    int find = 3; 
    IntIntEntry* iter;
    iter = rbtree_find(&tree, &find);
    assert(iter->key == 3);

    rbtree_remove(&tree, iter);
    free(iter);

    iter = rbtree_min(&tree);
    int expected[4] = {1, 2, 4, 5};
    int i = 0;
    for (; iter != NULL; iter = rbtree_next(&tree, iter)) {
        assert(iter->key == expected[i]);
        i++;
    }

    rbtree_free(&tree, NULL);
    test_largedata();
    printf("[PASS] rbtree\n");
    return 0;
}

#define TESTSZ 10000
int input[TESTSZ];

void shuffle(int *input, int n) {
    for (int i = n-1; i > 0; i--) {
        int j = rand() % i;
        int tmp = input[i];
        input[i] = input[j];
        input[j] = tmp;
    }
}

static void test_largedata() {
    // generate random input
    time_t t;
    srand((unsigned) time(&t));
    for (int i = 0; i < TESTSZ; i++) {
        input[i] = i;
    }
    shuffle(input, TESTSZ);
    // insert
    RbTree tree = {NULL, cmpfunc, NULL};
    IntIntEntry *n;
    for (int i = 0; i < TESTSZ; i ++) {
        n = malloc(sizeof(*n));
        n->key = input[i];
        n->value = input[i];
        rbtree_insert(&tree, n);
    }
    // check tree validity
    int d = depth(tree.rbh_root);
    assert(d >= 13 && d <= 28);
    IntIntEntry *iter = rbtree_min(&tree);
    int i = 0;
    for (; iter != NULL; iter = rbtree_next(&tree, iter)) {
        assert(iter->key == i);
        i++;
    }
    // delete when: key % 3 != 0
    memset(input, 0, sizeof(int) * TESTSZ);
    int count = 0;
    for (int i = 0; i < TESTSZ; i++) {
        if (i % 3 != 0) {
            input[count] = i;
        } else {
            continue;
        }
        count++;
    }
    shuffle(input, count);
    for (int i = 0; i < count; i++) {
        IntIntEntry *iter = rbtree_find(&tree, &input[i]);
        assert(iter != NULL);
        rbtree_remove(&tree, iter);
    }
    // check tree validity
    d = depth(tree.rbh_root);
    assert(d >= 11 && d <= 24);
    iter = rbtree_min(&tree);
    i = 0;
    for (; iter != NULL; iter = rbtree_next(&tree, iter)) {
        assert(iter->key == i*3);
        i++;
    }
}
