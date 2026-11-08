#include <cstdint>

using namespace std;

class Solution {
public:
  int reverseBits(int n) {
    uint32_t x = n, res = 0;
    for (int i = 0; i < 32; i++) {
      int bit = (x >> i) & 1;
      res = (res << 1) | bit;
    }
    return res;
  }
};
