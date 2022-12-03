#include <pque.h>
#include <stdio.h>
#include <assert.h>

int intcmp(void *_a, void *_b) {
    int a = *(int*)_a;
    int b = *(int*)_b;
    if (a < b) return 1;
    if (a > b) return -1;
    return 0;
}

int main() {
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
    printf("[PASSED] test_pque\n");
    return 0;
}
