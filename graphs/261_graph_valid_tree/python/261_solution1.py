from typing import List


class Solution:
    def validTree(self, n: int, edges: List[List[int]]) -> bool:
        count = n
        parent = list(range(n + 1))

        for a, b in edges:
            ra = self.find(parent, a)
            rb = self.find(parent, b)
            if ra == rb:
                return False
            count -= 1
            parent[rb] = ra
        return count == 1

    def find(self, parent: List[int], x: int) -> int:
        while parent[x] != x:
            x = parent[x]
        return x
