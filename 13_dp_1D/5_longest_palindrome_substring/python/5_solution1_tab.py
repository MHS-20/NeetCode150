class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        memo = [[False] * n for _ in range(n)]
        best_start, best_len = 0, 0

        for i in range(n - 1, -1, -1):
            for j in range(i, n):
                if s[i] == s[j] and (j - i < 2 or memo[i + 1][j - 1]):
                    memo[i][j] = True
                    if j - i + 1 > best_len:
                        best_start, best_len = i, j - i + 1

        return s[best_start : best_start + best_len]
