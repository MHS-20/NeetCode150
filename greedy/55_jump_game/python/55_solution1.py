from typing import List


class Solution:
    def canJump(self, nums: List[int]) -> bool:
        mx = 0

        for i, n in enumerate(nums):
            if i > mx:
                return False

            mx = max(mx, i + n)
            if mx >= len(nums) - 1:
                return True

        return False
