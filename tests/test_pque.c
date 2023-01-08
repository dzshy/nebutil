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
#include <stdio.h>
#include <stdlib.h>

#include "pque.h"

int intcmp(void *_a, void *_b)
{
    int a = *(int *)_a;
    int b = *(int *)_b;
    if (a < b)
        return 1;
    if (a > b)
        return -1;
    return 0;
}

int main()
{
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
