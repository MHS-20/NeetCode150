from typing import List


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        tot = sum(nums)
        if abs(target) > tot:
            return 0

        dp = [[0] * (2 * tot + 1) for _ in range(n + 1)]
        dp[0][0 + tot] = 1  # 0 numbers used, sum 0

        for i in range(1, n + 1):
            x = nums[i - 1]
            for s in range(-tot, tot + 1):
                ways = 0
                if s - x >= -tot:
                    ways += dp[i - 1][s - x + tot]  # added x
                if s + x <= tot:
                    ways += dp[i - 1][s + x + tot]  # subtracted x
                dp[i][s + tot] = ways
        return dp[n][target + tot]
