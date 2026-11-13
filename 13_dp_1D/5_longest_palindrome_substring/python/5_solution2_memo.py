class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        memo = [[None] * n for _ in range(n)]  # None unknown

        def is_pal(i: int, j: int) -> bool:
            if i >= j:
                return True  # length 0 or 1
            if memo[i][j] is None:
                memo[i][j] = s[i] == s[j] and is_pal(i + 1, j - 1)
            return memo[i][j]

        best_start, best_len = 0, 0
        for i in range(n):
            for j in range(i, n):
                if j - i + 1 > best_len and is_pal(i, j):
                    best_start, best_len = i, j - i + 1

        return s[best_start : best_start + best_len]
