from typing import List


class Solution:
    def foreignDictionary(self, words: List[str]) -> str:
        adj = {c: set() for w in words for c in w}  # 1. register every letter
        state = {c: 0 for c in adj}  # 0 = unvisited, 1 = visiting, 2 = done
        result = []

        # 2. Build edges (no in-degree needed)
        for a, b in zip(words, words[1:]):
            for x, y in zip(a, b):
                if x != y:
                    adj[x].add(y)  # duplicates are harmless here
                    break
            else:
                if len(a) > len(b):
                    return ""

        def dfs(u: str) -> bool:  # returns False if a cycle is found
            state[u] = 1
            for v in adj[u]:
                if state[v] == 1:
                    return False  # back edge: cycle
                if state[v] == 0 and not dfs(v):
                    return False  # propagate failure
            state[u] = 2
            result.append(u)  # post-order
            return True

        # 3. DFS from every unvisited letter
        for c in adj:
            if state[c] == 0 and not dfs(c):
                return ""

        # 4. Post-order is reversed topological order
        return "".join(reversed(result))
