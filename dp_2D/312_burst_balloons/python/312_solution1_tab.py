from typing import List


class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        a = [1] + nums + [1]  # pad: [1, nums..., 1]

        N = len(a)
        dp = [[0] * N for _ in range(N)]  # len < 2 → 0 already

        for length in range(2, N):  # distance between walls
            for l in range(N - length):
                r = l + length
                for k in range(l + 1, r):
                    dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + a[l] * a[k] * a[r])
        return dp[0][N - 1]
