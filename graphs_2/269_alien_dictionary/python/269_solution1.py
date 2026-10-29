from collections import deque
from typing import List


class Solution:
    def foreignDictionary(self, words: List[str]) -> str:
        adj = {c: set() for w in words for c in w}
        indeg = {c: 0 for c in adj}

        for a, b in zip(words, words[1:]):
            for x, y in zip(a, b):
                if x != y:
                    if y not in adj[x]:  # avoid double-counting
                        adj[x].add(y)
                        indeg[y] += 1
                    break
            else:
                if len(a) > len(b):
                    return ""  # b is a proper prefix of a: invalid

        # Kahn's algorithm
        q = deque(c for c in indeg if indeg[c] == 0)
        result = []
        while q:
            u = q.popleft()
            result.append(u)
            for v in adj[u]:
                indeg[v] -= 1
                if indeg[v] == 0:
                    q.append(v)

        return "".join(result) if len(result) == len(adj) else ""
