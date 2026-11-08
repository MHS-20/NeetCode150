from typing import List


class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        res = len(nums)
        for i, n in enumerate(nums):
            res ^= i ^ n
        return res
