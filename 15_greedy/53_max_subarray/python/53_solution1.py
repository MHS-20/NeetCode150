from typing import List


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        total = 0
        mx = float("-inf")

        for n in nums:
            total += n
            mx = max(total, mx)
            if total < 0:
                total = 0 if n < 0 else n

        return mx
