from typing import List

DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        rows, cols = len(heights), len(heights[0])
        pacific = [[False] * cols for _ in range(rows)]
        atlantic = [[False] * cols for _ in range(rows)]

        def dfs(ocean: List[List[bool]], r: int, c: int, prev_height: float) -> None:
            if r < 0 or c < 0 or r >= rows or c >= cols:
                return
            if ocean[r][c] or heights[r][c] < prev_height:
                return

            ocean[r][c] = True
            for dr, dc in DIRS:
                dfs(ocean, r + dr, c + dc, heights[r][c])

        for i in range(rows):
            dfs(pacific, i, 0, float("-inf"))
            dfs(atlantic, i, cols - 1, float("-inf"))
        for j in range(cols):
            dfs(pacific, 0, j, float("-inf"))
            dfs(atlantic, rows - 1, j, float("-inf"))

        return [
            [i, j]
            for i in range(rows)
            for j in range(cols)
            if pacific[i][j] and atlantic[i][j]
        ]
