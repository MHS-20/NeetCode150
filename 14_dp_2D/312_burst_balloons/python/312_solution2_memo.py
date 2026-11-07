from typing import List


class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        a = [1] + nums + [1]  # pad: [1, nums..., 1]

        N = len(a)
        dp = [[-1] * N for _ in range(N)]

        def f(l: int, r: int) -> int:
            if r - l < 2:
                return 0  # nothing strictly between l and r
            if dp[l][r] != -1:
                return dp[l][r]

            best = 0
            for k in range(l + 1, r):  # k = last balloon burst in (l, r)
                coins = a[l] * a[k] * a[r] + f(l, k) + f(k, r)
                best = max(best, coins)
            dp[l][r] = best
            return best

        return f(0, N - 1)
