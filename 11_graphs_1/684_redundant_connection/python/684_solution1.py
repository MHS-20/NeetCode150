from typing import List


class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        parent = list(range(n + 1))

        for edge in edges:
            ra = self.find(parent, edge[0])
            rb = self.find(parent, edge[1])
            if ra == rb:
                return edge
            parent[rb] = ra
        return []

    def find(self, parent: List[int], x: int) -> int:
        while parent[x] != x:
            x = parent[x]
        return x
