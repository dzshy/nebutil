#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pque.h"

int intcmp(void *_a, void *_b) {
    int a = *(int*)_a;
    int b = *(int*)_b;
    if (a < b) return 1;
    if (a > b) return -1;
    return 0;
}

int main() {
    printf("[TEST] pque\n");
    PQue pq;
    pq_init(&pq, 3, sizeof(int), intcmp);
    int elems[10] = {1, 3, 2, 4, 6, 5, 9, 7, 8, 10};
    for (int i = 0; i < 10; i++) {
        int e = elems[i];
        pq_push(&pq, &e);
    }
    for (int i = 1; i < 11; i++) {
        int *top = pq_top(&pq);
        assert(i == *top);
        pq_pop(&pq);
    }
    assert(pq_top(&pq) == NULL);
    int elems2[10] = {10, 8, 7, 9, 5, 6, 4, 2, 3, 1};
    int expected[10] = {10, 8, 7, 7, 5, 5, 4, 2, 2, 1};
    for (int i = 0; i < 10; i++) {
        int e = elems2[i];
        pq_push(&pq, &e);
        int *top = pq_top(&pq);
        assert(*top == expected[i]);
    }
    printf("[PASS] pque\n");
    return 0;
}
