from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        result: List[List[str]] = []
        board = [["."] * n for _ in range(n)]
        cols = [False] * n
        diag1 = [False] * (2 * n - 1)
        diag2 = [False] * (2 * n - 1)

        def backtrack(row: int) -> None:
            if row == n:
                result.append(["".join(r) for r in board])
                return

            for col in range(n):
                d1 = row + col  # "/" diagonal
                d2 = row - col + n - 1  # "\" diagonal, shifted
                if cols[col] or diag1[d1] or diag2[d2]:
                    continue

                board[row][col] = "Q"
                cols[col] = diag1[d1] = diag2[d2] = True

                backtrack(row + 1)

                board[row][col] = "."
                cols[col] = diag1[d1] = diag2[d2] = False

        backtrack(0)
        return result
