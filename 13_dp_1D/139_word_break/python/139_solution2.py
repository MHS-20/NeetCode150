from typing import List


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        n = len(s)
        words = set(wordDict)
        max_len = max(len(w) for w in wordDict)

        dp = [False] * (n + 1)
        dp[0] = True

        for i in range(1, n + 1):
            # A piece longer than max_len can't be a word, so start j no earlier
            # than i - max_len
            for j in range(max(0, i - max_len), i):
                if dp[j] and s[j:i] in words:
                    dp[i] = True
                    break
        return dp[n]
