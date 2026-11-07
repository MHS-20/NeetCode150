class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [[-1] * n for _ in range(m)]

        def solve(i: int, j: int) -> int:
            if i == 0 and j == 0:
                return 1  # reached the start
            if i < 0 or j < 0:
                return 0  # fell off the grid
            if dp[i][j] != -1:
                return dp[i][j]  # already computed

            up = solve(i - 1, j)
            left = solve(i, j - 1)
            dp[i][j] = up + left
            return dp[i][j]

        return solve(m - 1, n - 1)
