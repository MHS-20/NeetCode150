from typing import List

DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        rows, cols = len(board), len(board[0])

        def dfs(r: int, c: int) -> None:
            if r < 0 or c < 0 or r >= rows or c >= cols or board[r][c] != "O":
                return
            board[r][c] = "."
            for dr, dc in DIRS:
                dfs(r + dr, c + dc)

        # 1. mark border-connected 'O's as safe
        for i in range(rows):
            dfs(i, 0)
            dfs(i, cols - 1)
        for j in range(cols):
            dfs(0, j)
            dfs(rows - 1, j)

        # 2. capture leftover 'O's, restore safe ones
        for row in board:
            for j, cell in enumerate(row):
                if cell == "O":
                    row[j] = "X"
                elif cell == ".":
                    row[j] = "O"
