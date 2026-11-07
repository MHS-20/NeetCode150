class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        best_start, best_len = 0, 1

        # Every single character is a palindrome
        for i in range(n):
            dp[i][i] = True

        # Fill by increasing substring length
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1

                if s[i] == s[j] and (length == 2 or dp[i + 1][j - 1]):
                    dp[i][j] = True
                    if length > best_len:
                        best_start, best_len = i, length

        return s[best_start : best_start + best_len]
