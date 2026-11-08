# Swap the two 16-bit halves.
# Within each half, swap the 8-bit halves.
# Then swap 4-bit groups, then 2-bit groups, then single bits
class Solution:
    def reverseBits(self, n: int) -> int:
        M = 0xFFFFFFFF  # Python ints are unbounded, so << must be masked to 32 bits
        x = n
        x = ((x >> 16) | (x << 16)) & M
        x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8)
        x = ((x & 0xF0F0F0F0) >> 4) | ((x & 0x0F0F0F0F) << 4)
        x = ((x & 0xCCCCCCCC) >> 2) | ((x & 0x33333333) << 2)
        x = ((x & 0xAAAAAAAA) >> 1) | ((x & 0x55555555) << 1)
        return x
