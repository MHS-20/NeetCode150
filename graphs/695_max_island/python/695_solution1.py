from typing import List

DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        if not grid:
            return 0

        mx = 0
        rows, cols = len(grid), len(grid[0])

        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == 1:
                    mx = max(self.sink(grid, i, j, rows, cols), mx)
        return mx

    def sink(self, grid: List[List[int]], r: int, c: int, rows: int, cols: int) -> int:
        if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] != 1:
            return 0
        grid[r][c] = 0
        count = 1
        for dr, dc in DIRS:
            count += self.sink(grid, r + dr, c + dc, rows, cols)
        return count
