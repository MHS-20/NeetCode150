from typing import List


class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        n = len(coins)
        dp = [[0] * (amount + 1) for _ in range(n + 1)]
        for i in range(n + 1):
            dp[i][0] = 1  # one way to make 0: use nothing

        for i in range(1, n + 1):
            for x in range(1, amount + 1):
                dp[i][x] = dp[i - 1][x]  # skip coin i
                if coins[i - 1] <= x:
                    dp[i][x] += dp[i][x - coins[i - 1]]  # take coin i (same row)
        return dp[n][amount]
