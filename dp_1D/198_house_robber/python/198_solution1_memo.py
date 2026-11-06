from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        memo = [-1] * len(nums)

        def max_loot(idx: int) -> int:
            if idx == 0:
                return nums[0]
            if idx == 1:
                return max(nums[0], nums[1])

            if memo[idx] != -1:
                return memo[idx]

            memo[idx] = max(
                max_loot(idx - 1),  # skip this house
                max_loot(idx - 2) + nums[idx],  # rob this house
            )
            return memo[idx]

        return max_loot(len(nums) - 1)
