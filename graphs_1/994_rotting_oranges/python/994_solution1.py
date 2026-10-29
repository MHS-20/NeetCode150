from collections import deque
from typing import List

DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        q = deque()
        fresh = 0

        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == 2:
                    q.append((i, j))
                elif grid[i][j] == 1:
                    fresh += 1

        minutes = 0
        while q and fresh > 0:
            minutes += 1
            for _ in range(len(q)):
                r, c = q.popleft()
                for dr, dc in DIRS:
                    nr, nc = r + dr, c + dc
                    if nr < 0 or nc < 0 or nr >= rows or nc >= cols:
                        continue
                    if grid[nr][nc] != 1:
                        continue

                    grid[nr][nc] = 2
                    fresh -= 1
                    q.append((nr, nc))
        return minutes if fresh == 0 else -1
