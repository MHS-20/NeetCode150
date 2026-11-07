class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        seenRows = [[False] * 9 for _ in range(9)]
        seenCols = [[False] * 9 for _ in range(9)]
        seenBoxes = [[False] * 9 for _ in range(9)]

        def checkAndMark(arr: list[bool], idx: int) -> bool:
            if arr[idx]:
                return False
            arr[idx] = True
            return True

        for i in range(9):
            for j in range(9):
                if board[i][j] == ".":
                    continue

                current = int(board[i][j]) - 1
                box = (i // 3) * 3 + (j // 3)

                if not checkAndMark(seenRows[i], current):
                    return False
                if not checkAndMark(seenCols[j], current):
                    return False
                if not checkAndMark(seenBoxes[box], current):
                    return False

        return True
