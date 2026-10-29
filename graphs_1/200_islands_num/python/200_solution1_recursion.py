from typing import List

DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid:
            return 0
        rows, cols = len(grid), len(grid[0])
        count = 0
        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == "1":
                    self.sink(grid, i, j, rows, cols)
                    count += 1
        return count

    def sink(self, grid: List[List[str]], r: int, c: int, rows: int, cols: int) -> None:
        if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] != "1":
            return
        grid[r][c] = "0"
        for dr, dc in DIRS:
            self.sink(grid, r + dr, c + dc, rows, cols)
