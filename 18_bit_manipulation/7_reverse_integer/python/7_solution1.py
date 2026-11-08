import math

INT_MAX, INT_MIN = 2**31 - 1, -(2**31)


class Solution:
    def reverse(self, x: int) -> int:
        res = 0

        while x != 0:
            # Python's // and % round toward -inf: use C-style truncation
            d = int(math.fmod(x, 10))
            x = int(x / 10)

            if res > INT_MAX // 10 or res < int(INT_MIN / 10):
                return 0
            res = res * 10 + d

        return res
