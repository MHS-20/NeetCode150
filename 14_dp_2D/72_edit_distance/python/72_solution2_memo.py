import sys


class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        sys.setrecursionlimit(max(1000, 2 * (n + m) + 100))  # depth can reach n + m
        dp = [[-1] * (m + 1) for _ in range(n + 1)]

        def f(i: int, j: int) -> int:
            if i == 0:
                return j  # insert the remaining j chars
            if j == 0:
                return i  # delete the remaining i chars
            if dp[i][j] != -1:
                return dp[i][j]

            if word1[i - 1] == word2[j - 1]:
                dp[i][j] = f(i - 1, j - 1)  # free match
                return dp[i][j]

            delete = f(i - 1, j)
            insert = f(i, j - 1)
            replace = f(i - 1, j - 1)
            dp[i][j] = 1 + min(delete, insert, replace)
            return dp[i][j]

        return f(n, m)
