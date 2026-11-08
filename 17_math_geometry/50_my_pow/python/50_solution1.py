class Solution:
    def myPow(self, x: float, n: int) -> float:
        neg = n < 0
        N = -n if neg else n

        res = 1.0
        while N > 0:
            if N & 1:
                res *= x
            x *= x
            N >>= 1
        return 1 / res if neg else res
