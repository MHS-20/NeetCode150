class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)
        count = 0
        dp = [[False] * n for _ in range(n)]

        for i in range(n):
            dp[i][i] = True
            count += 1

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1

                if s[i] == s[j] and (length == 2 or dp[i + 1][j - 1]):
                    dp[i][j] = True
                    count += 1

        return count
