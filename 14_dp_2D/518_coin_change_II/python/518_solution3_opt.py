from typing import List


class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        dp = [0] * (amount + 1)
        dp[0] = 1
        for c in coins:
            for x in range(c, amount + 1):
                dp[x] += dp[x - c]
        return dp[amount]
