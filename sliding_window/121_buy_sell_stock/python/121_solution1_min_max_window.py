class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        mn = float("inf")
        profit = 0

        for p in prices:
            mn = min(mn, p)
            profit = max(profit, p - mn)

        return profit
