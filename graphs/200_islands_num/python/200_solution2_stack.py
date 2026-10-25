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
        st = [(r, c)]
        grid[r][c] = "0"
        while st:
            cr, cc = st.pop()
            for dr, dc in DIRS:
                nr, nc = cr + dr, cc + dc
                if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == "1":
                    grid[nr][nc] = "0"
                    st.append((nr, nc))
