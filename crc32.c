#include "crc32.h"

uint32_t crc32(uint32_t r, void* buf, int size) {
  r = ~r;
  uint8_t *data = buf;
  uint8_t *end = data + size;
  while(data < end){
      r ^= *data++;
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
      r = (r>>1) ^ (0xEDB88320 & (~((r&1) - 1)));
  }
  return ~r;
}

