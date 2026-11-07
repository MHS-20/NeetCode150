import heapq
from typing import List


class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)
        visited = [[False] * n for _ in range(n)]
        pq = [(grid[0][0], 0, 0)]  # (elev, r, c)
        visited[0][0] = True
        t = 0

        while pq:
            elev, r, c = heapq.heappop(pq)
            t = max(t, elev)
            if r == n - 1 and c == n - 1:
                return t

            for dr, dc in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                nr, nc = r + dr, c + dc
                if nr < 0 or nc < 0 or nr >= n or nc >= n or visited[nr][nc]:
                    continue
                visited[nr][nc] = True
                heapq.heappush(pq, (grid[nr][nc], nr, nc))
        return -1
