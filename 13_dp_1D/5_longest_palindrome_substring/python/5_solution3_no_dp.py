class Solution:
    def longestPalindrome(self, s: str) -> str:
        best_start, best_len = 0, 0

        def expand(l: int, r: int) -> None:
            nonlocal best_start, best_len
            # bounds first, so s[l] and s[r] are only read when valid
            while l >= 0 and r < len(s) and s[l] == s[r]:
                l -= 1
                r += 1
            # pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
            length = r - l - 1
            if length > best_len:
                best_start, best_len = l + 1, length

        for i in range(len(s)):
            # odd-length palindromes, centered on s[i]
            expand(i, i)
            # even-length palindromes, centered between s[i] and s[i+1]
            expand(i, i + 1)

        return s[best_start : best_start + best_len]
