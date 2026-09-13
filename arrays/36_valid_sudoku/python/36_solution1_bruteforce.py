class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        seen = [False] * 9

        for i in range(9):
            for j in range(9):
                if board[i][j] == ".":
                    continue
                current = int(board[i][j]) - 1
                if seen[current]:
                    return False
                seen[current] = True
            seen = [False] * 9

        for j in range(9):
            for i in range(9):
                if board[i][j] == ".":
                    continue
                current = int(board[i][j]) - 1
                if seen[current]:
                    return False
                seen[current] = True
            seen = [False] * 9

        for rowOffset in range(0, 9, 3):
            for colOffset in range(0, 9, 3):
                for i in range(3):
                    for j in range(3):
                        val = board[i + rowOffset][j + colOffset]
                        if val == ".":
                            continue
                        current = int(val) - 1
                        if seen[current]:
                            return False
                        seen[current] = True
                seen = [False] * 9

        return True
