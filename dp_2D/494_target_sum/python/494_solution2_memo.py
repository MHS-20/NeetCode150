from typing import List


class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        tot = sum(nums)
        if abs(target) > tot:
            return 0

        dp = [[-1] * (2 * tot + 1) for _ in range(n)]  # dp[i][sum + tot], -1 = not computed

        def f(i: int, total: int) -> int:
            """Ways to reach target using nums[i:], given the running sum so far."""
            if i == n:
                return 1 if total == target else 0
            if dp[i][total + tot] != -1:
                return dp[i][total + tot]

            add = f(i + 1, total + nums[i])  # +nums[i]
            sub = f(i + 1, total - nums[i])  # -nums[i]
            dp[i][total + tot] = add + sub
            return dp[i][total + tot]

        return f(0, 0)
