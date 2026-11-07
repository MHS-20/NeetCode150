from typing import List


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        result: List[List[str]] = []
        path: List[str] = []

        def backtrack(start: int) -> None:
            if start == len(s):
                result.append(path[:])
                return
            for i in range(start, len(s)):
                if not self.isPalindrome(s, start, i):
                    continue
                path.append(s[start : i + 1])
                backtrack(i + 1)
                path.pop()

        backtrack(0)
        return result

    def isPalindrome(self, s: str, l: int, r: int) -> bool:
        while l < r:
            if s[l] != s[r]:
                return False
            l, r = l + 1, r - 1
        return True
