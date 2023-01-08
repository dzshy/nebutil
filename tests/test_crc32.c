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
#include <string.h>

#include "crc32.h"

int main()
{
    printf("[TEST] crc32\n");
    char buf[] = "hello, world\n";
    uint32_t crc = crc32(0, buf, strlen(buf));
    assert(crc == 0xf4247453);
    crc = crc32(0, buf, 3);
    crc = crc32(crc, buf + 3, strlen(buf) - 3);
    assert(crc == 0xf4247453);
    printf("[PASS] crc32\n");
    return 0;
}
