from collections import deque
from string import ascii_lowercase
from typing import List


class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        words = set(wordList)
        if endWord not in words:
            return 0

        q = deque([beginWord])
        words.discard(beginWord)
        length = 1

        while q:
            for _ in range(len(q)):
                w = list(q.popleft())

                for pos in range(len(w)):
                    original = w[pos]
                    for c in ascii_lowercase:
                        if c == original:
                            continue
                        w[pos] = c
                        s = "".join(w)
                        if s == endWord:
                            return length + 1
                        if s in words:
                            words.remove(s)
                            q.append(s)
                    w[pos] = original
            length += 1
        return 0
