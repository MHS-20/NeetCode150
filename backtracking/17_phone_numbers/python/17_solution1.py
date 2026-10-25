from typing import List

MAPPING = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        result: List[str] = []
        if not digits:
            return result
        cur: List[str] = []

        def backtrack(idx: int) -> None:
            if idx == len(digits):
                result.append("".join(cur))
                return
            for ch in MAPPING[int(digits[idx])]:
                cur.append(ch)  # choose
                backtrack(idx + 1)
                cur.pop()  # un-choose

        backtrack(0)
        return result
