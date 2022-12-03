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
    RbTree head = {NULL, int_cmp};
    IntIntEntry *n;

    int a[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i ++) {
        n = malloc(sizeof(*n));
        n->key = a[i];
        n->value = i;

        rbtree_insert(&head, (RbNode*)n);
    }
    
    int find = 3; 
    IntIntEntry* iter;
    iter = (IntIntEntry*)rbtree_find(&head, &find);
    assert(iter->key == 3);
    
    rbtree_remove(&head, (RbNode*)iter);
    free(iter);
    
    iter = (IntIntEntry*)rbtree_min(&head);
    int expected[4] = {1, 2, 4, 5};
    int i = 0;
    for (; iter != NULL; iter = (IntIntEntry*)rbtree_next(&head, (RbNode*)iter)) {
        assert(iter->key == expected[i]);
        i++;
    }

    rbtree_free(&head, NULL);
    printf("[PASSED] test_rbtree\n");
    return 0;
}
