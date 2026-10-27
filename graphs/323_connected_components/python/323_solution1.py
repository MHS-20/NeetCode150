from typing import List


class Solution:
    def countComponents(self, n: int, edges: List[List[int]]) -> int:
        parent = list(range(n + 1))
        count = n

        for a, b in edges:
            ra = self.find(parent, a)
            rb = self.find(parent, b)
            if ra != rb:
                count -= 1
            parent[rb] = ra
        return count

    def find(self, parent: List[int], x: int) -> int:
        while parent[x] != x:
            x = parent[x]
        return x
