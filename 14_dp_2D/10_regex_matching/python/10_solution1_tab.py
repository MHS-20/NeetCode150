class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n, m = len(s), len(p)
        dp = [[False] * (m + 1) for _ in range(n + 1)]
        dp[0][0] = True

        def matches(i: int, j: int) -> bool:  # s[i-1] vs p[j-1]
            return p[j - 1] == "." or s[i - 1] == p[j - 1]

        for i in range(n + 1):
            for j in range(1, m + 1):
                if p[j - 1] == "*":
                    dp[i][j] = dp[i][j - 2]  # zero copies
                    if i > 0 and matches(i, j - 1):
                        dp[i][j] = dp[i][j] or dp[i - 1][j]  # one more copy
                else:
                    dp[i][j] = i > 0 and matches(i, j) and dp[i - 1][j - 1]
        return dp[n][m]
