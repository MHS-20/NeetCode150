class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        n, m = len(s1), len(s2)
        if n + m != len(s3):
            return False

        dp = [[False] * (m + 1) for _ in range(n + 1)]
        dp[0][0] = True  # empty + empty = empty

        for i in range(n + 1):
            for j in range(m + 1):
                if i == 0 and j == 0:
                    continue
                k = i + j - 1  # last char of s3 prefix
                from_s1 = i > 0 and dp[i - 1][j] and s1[i - 1] == s3[k]
                from_s2 = j > 0 and dp[i][j - 1] and s2[j - 1] == s3[k]
                dp[i][j] = from_s1 or from_s2
        return dp[n][m]
