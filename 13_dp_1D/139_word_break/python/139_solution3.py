from typing import List


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True

        for i in range(1, n + 1):
            for w in wordDict:
                length = len(w)
                # Does word w end exactly at position i?
                if length <= i and dp[i - length] and s.startswith(w, i - length):
                    dp[i] = True
                    break
        return dp[n]
