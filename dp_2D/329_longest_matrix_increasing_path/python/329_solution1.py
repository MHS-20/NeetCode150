import sys
from typing import List


class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        m, n = len(matrix), len(matrix[0])
        sys.setrecursionlimit(max(1000, m * n + 100))  # a path can visit every cell
        dp = [[0] * n for _ in range(m)]  # 0 = not computed

        def dfs(i: int, j: int) -> int:
            if dp[i][j] != 0:
                return dp[i][j]  # already computed

            best = 1  # the cell alone
            for di, dj in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                ni, nj = i + di, j + dj
                if 0 <= ni < m and 0 <= nj < n and matrix[ni][nj] > matrix[i][j]:
                    best = max(best, 1 + dfs(ni, nj))
            dp[i][j] = best
            return best

        return max(dfs(i, j) for i in range(m) for j in range(n))
