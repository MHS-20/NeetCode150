from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 1:
            return nums[0]

        def rob_range(start: int, end: int) -> int:
            """Max loot from houses start..end (inclusive), in a straight line."""
            length = end - start + 1
            if length == 1:
                return nums[start]

            dp = [0] * length
            dp[0] = nums[start]
            dp[1] = max(nums[start], nums[start + 1])

            for i in range(2, length):
                dp[i] = max(
                    dp[i - 1],  # skip this house
                    dp[i - 2] + nums[start + i],  # rob this house
                )
            return dp[length - 1]

        return max(
            rob_range(0, n - 2),  # exclude the last house
            rob_range(1, n - 1),  # exclude the first house
        )
