class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        seenGrid = [False] * 9
        seenCol = [[False] * 9 for _ in range(9)]
        seenRow = [[False] * 9 for _ in range(9)]

        for rowOffset in range(0, 9, 3):
            for colOffset in range(0, 9, 3):
                for i in range(3):
                    for j in range(3):
                        val = board[i + rowOffset][j + colOffset]
                        if val == ".":
                            continue

                        current = int(val) - 1

                        if seenGrid[current]:
                            return False
                        seenGrid[current] = True

                        if seenRow[i + rowOffset][current]:
                            return False
                        seenRow[i + rowOffset][current] = True

                        if seenCol[j + colOffset][current]:
                            return False
                        seenCol[j + colOffset][current] = True

                seenGrid = [False] * 9

        return True
