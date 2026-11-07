import sys
from typing import List


class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        sys.setrecursionlimit(max(1000, 2 * (len(coins) + amount) + 100))  # deep recursion
        dp = [[-1] * (amount + 1) for _ in range(len(coins))]

        def f(i: int, x: int) -> int:
            if x == 0:
                return 1  # made the amount
            if i == len(coins):
                return 0  # out of coins
            if dp[i][x] != -1:
                return dp[i][x]

            skip = f(i + 1, x)  # never use coin i again
            take = 0
            if coins[i] <= x:
                take = f(i, x - coins[i])  # use coin i, stay at i (reuse allowed)

            dp[i][x] = skip + take
            return dp[i][x]

        return f(0, amount)
