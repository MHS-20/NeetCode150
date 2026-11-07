from typing import List, Optional


class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        n, m = len(s), len(p)
        dp: List[List[Optional[bool]]] = [[None] * (m + 1) for _ in range(n + 1)]

        def matches(i: int, j: int) -> bool:  # s[i-1] vs p[j-1]
            return p[j - 1] == "." or s[i - 1] == p[j - 1]

        def f(i: int, j: int) -> bool:
            if j == 0:
                return i == 0  # empty pattern matches only empty s
            if dp[i][j] is not None:
                return dp[i][j]

            if p[j - 1] == "*":
                res = f(i, j - 2)  # zero copies
                if not res and i > 0 and matches(i, j - 1):
                    res = f(i - 1, j)  # one more copy
            else:
                res = i > 0 and matches(i, j) and f(i - 1, j - 1)

            dp[i][j] = res
            return res

        return f(n, m)
