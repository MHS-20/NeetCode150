import sys
from typing import List, Optional


class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        n, m = len(s1), len(s2)
        if n + m != len(s3):
            return False

        sys.setrecursionlimit(max(1000, 2 * (n + m) + 100))  # depth can reach n + m
        dp: List[List[Optional[bool]]] = [[None] * (m + 1) for _ in range(n + 1)]

        def f(i: int, j: int) -> bool:
            if i == n and j == m:
                return True  # used everything
            if dp[i][j] is not None:
                return dp[i][j]

            k = i + j  # position in s3
            res = False
            if i < n and s1[i] == s3[k]:
                res = f(i + 1, j)  # take from s1
            if not res and j < m and s2[j] == s3[k]:
                res = f(i, j + 1)  # take from s2

            dp[i][j] = res
            return res

        return f(0, 0)
