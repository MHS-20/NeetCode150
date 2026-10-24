from typing import List

DIRS = ((1, 0), (0, 1), (-1, 0), (0, -1))


class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        rows, cols = len(board), len(board[0])

        def dfs(idx: int, row: int, col: int) -> bool:
            ch = word[idx]
            if ch != board[row][col]:
                return False

            if idx == len(word) - 1:
                return True

            board[row][col] = "#"
            for dr, dc in DIRS:
                nr, nc = row + dr, col + dc

                if nr < 0 or nr >= rows or nc < 0 or nc >= cols:
                    continue

                if dfs(idx + 1, nr, nc):
                    return True

            board[row][col] = ch
            return False

        return any(dfs(0, r, c) for r in range(rows) for c in range(cols))
