class Solution:
    def isValidSudoku(self, board: list[list[str]]) -> bool:
        seenRows = [0] * 9
        seenCols = [0] * 9
        seenBoxes = [0] * 9

        def checkAndMark(masks: list[int], idx: int, bit: int) -> bool:
            if masks[idx] & (1 << bit):
                return False
            masks[idx] |= 1 << bit
            return True

        for i in range(9):
            for j in range(9):
                if board[i][j] == ".":
                    continue

                current = int(board[i][j]) - 1
                box = (i // 3) * 3 + (j // 3)

                if not checkAndMark(seenRows, i, current):
                    return False
                if not checkAndMark(seenCols, j, current):
                    return False
                if not checkAndMark(seenBoxes, box, current):
                    return False

        return True
