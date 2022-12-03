#include <stdio.h>
#include <assert.h>

#include "rbtree.h"

int int_cmp(void *a, void *b) {
    int *pa = (int*)a;
    int *pb = (int*)b;
    return *pa < *pb ?  -1 : *pa > *pb;
}

typedef struct {
    RbNode node;
    int key;
    int value;
} IntIntEntry;

int main() {
    RbTree tree = {NULL, int_cmp};
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
    printf("[PASSED] test_rbtree\n");
    return 0;
}
