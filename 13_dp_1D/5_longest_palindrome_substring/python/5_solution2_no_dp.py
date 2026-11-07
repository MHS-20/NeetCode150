class Solution:
    def longestPalindrome(self, s: str) -> str:
        def expand(left: int, right: int) -> int:
            """Grow outward from the center (left, right) while the ends match.
            Returns the length of the palindrome found."""
            while left >= 0 and right < len(s) and s[left] == s[right]:
                left -= 1
                right += 1
            return right - left - 1

        best_start, best_len = 0, 0

        for i in range(len(s)):
            odd_len = expand(i, i)  # center on a character: "aba"
            even_len = expand(i, i + 1)  # center between two characters: "abba"
            length = max(odd_len, even_len)

            if length > best_len:
                best_len = length
                best_start = i - (length - 1) // 2

        return s[best_start : best_start + best_len]
