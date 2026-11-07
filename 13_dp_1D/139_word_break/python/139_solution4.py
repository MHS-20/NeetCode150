from typing import List


class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_word = False


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        # Build the trie from the dictionary
        root = TrieNode()
        for w in wordDict:
            node = root
            for c in w:
                node = node.children.setdefault(c, TrieNode())
            node.is_word = True

        n = len(s)
        dp = [False] * (n + 1)
        dp[0] = True

        for j in range(n):
            if not dp[j]:
                continue  # only start a word where the prefix is segmentable

            # Walk s and the trie together, starting at j
            node = root
            for k in range(j, n):
                node = node.children.get(s[k])
                if node is None:
                    break  # no dictionary word continues this way
                if node.is_word:
                    dp[k + 1] = True  # s[j..k] is a word, so the first k+1 chars are segmentable
        return dp[n]
