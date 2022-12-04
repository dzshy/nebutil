#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "crc32.h"

int main() {
    printf("[TEST] crc32\n");
    char buf[] = "hello, world\n";
    uint32_t crc = crc32(0, buf, strlen(buf));
    assert(crc == 0xf4247453);
    crc = crc32(0, buf, 3);
    crc = crc32(crc, buf+3, strlen(buf) - 3);
    assert(crc == 0xf4247453);
    printf("[PASS] crc32\n\n");
    return 0;
}
