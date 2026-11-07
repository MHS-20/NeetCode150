import sys


class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        sys.setrecursionlimit(max(1000, n + 100))  # depth can reach len(s)
        dp = [[-1] * (m + 1) for _ in range(n + 1)]

        def f(i: int, j: int) -> int:
            if j == 0:
                return 1  # t fully matched
            if i == 0:
                return 0  # s ran out first
            if dp[i][j] != -1:
                return dp[i][j]

            ways = f(i - 1, j)  # skip s[i-1]
            if s[i - 1] == t[j - 1]:
                ways += f(i - 1, j - 1)  # pick it

            dp[i][j] = ways
            return ways

        return f(n, m)
