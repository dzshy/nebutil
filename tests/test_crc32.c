#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "crc32.h"

int main() {
    char buf[] = "hello, world\n";
    uint32_t crc = crc32(0, buf, strlen(buf));
    assert(crc == 0xf4247453);
    crc = crc32(0, buf, 3);
    crc = crc32(crc, buf+3, strlen(buf) - 3);
    assert(crc == 0xf4247453);
    printf("[PASSED] test_crc32\n");
    return 0;
}
