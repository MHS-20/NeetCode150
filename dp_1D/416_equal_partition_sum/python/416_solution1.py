from typing import List


class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        total = sum(nums)
        if total % 2 != 0:
            return False
        target = total // 2

        dp = [False] * (target + 1)
        dp[0] = True

        for x in nums:
            # Go backward so each number is used at most once
            for s in range(target, x - 1, -1):
                if dp[s - x]:
                    dp[s] = True
        return dp[target]
