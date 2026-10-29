from collections import deque
from typing import List

INF = 2147483647
DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def islandsAndTreasure(self, grid: List[List[int]]) -> None:
        rows, cols = len(grid), len(grid[0])
        q = deque((i, j) for i in range(rows) for j in range(cols) if grid[i][j] == 0)

        while q:
            r, c = q.popleft()
            for dr, dc in DIRS:
                nr, nc = r + dr, c + dc
                if nr < 0 or nc < 0 or nr >= rows or nc >= cols:
                    continue
                if grid[nr][nc] != INF:
                    continue

                grid[nr][nc] = grid[r][c] + 1
                q.append((nr, nc))
