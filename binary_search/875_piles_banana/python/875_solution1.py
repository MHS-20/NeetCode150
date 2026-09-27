import math


class Solution:
    def minEatingSpeed(self, piles: list[int], h: int) -> int:
        left, right = 1, max(piles)

        while left < right:
            k = left + (right - left) // 2
            hours = sum(math.ceil(p / k) for p in piles)

            if hours > h:
                left = k + 1
            else:
                right = k
        return left
