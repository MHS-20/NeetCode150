#include <stdint.h>

uint32_t reverseBits(uint32_t n) {
  uint32_t res = 0;
  for (int i = 0; i < 32; i++) {
    uint32_t bit = (n >> i) & 1;
    res = (res << 1) | bit;
  }
  return res;
}
