#include <stdio.h>

#include "rbtree.h"

int int_cmp(void *a, void *b) {
    int *pa = (int*)a;
    int *pb = (int*)b;
    return *pa < *pb ?  -1 : *pa > *pb;
}

typedef struct {
    struct rbnode;
    int key;
    int value;
} IntIntEntry;

typedef struct rbnode RbNode;

int main() {
    struct rbtree head = {NULL, int_cmp};
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
    printf("%d\n", iter->key);
    
    rbtree_remove(&head, (RbNode*)iter);
    free(iter);

    printf("--------------\n");
    
    iter = (IntIntEntry*)rbtree_min(&head);
    for (; iter != NULL; iter = (IntIntEntry*)rbtree_next(&head, (RbNode*)iter)) {
        printf("%d\n", iter->key);
    }

    rbtree_free(&head, NULL);
    
    return 0;
}
