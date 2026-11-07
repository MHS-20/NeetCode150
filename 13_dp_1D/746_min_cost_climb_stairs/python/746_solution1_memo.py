from typing import List


class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        memo = [-1] * (len(cost) + 1)

        def costs(i: int) -> int:
            if i <= 1:
                return 0  # start on step 0 or 1 for free
            if memo[i] != -1:
                return memo[i]
            memo[i] = min(costs(i - 1) + cost[i - 1], costs(i - 2) + cost[i - 2])
            return memo[i]

        return costs(len(cost))
