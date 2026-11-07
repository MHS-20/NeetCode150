from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [[0, 0] for _ in range(n + 2)]  # dp[day][can_buy]

        for day in range(n - 1, -1, -1):
            # can_buy = 1
            dp[day][1] = max(
                -prices[day] + dp[day + 1][0],  # buy
                dp[day + 1][1],  # skip
            )
            # can_buy = 0 (holding)
            dp[day][0] = max(
                prices[day] + dp[day + 2][1],  # sell + cooldown
                dp[day + 1][0],  # hold
            )
        return dp[0][1]
