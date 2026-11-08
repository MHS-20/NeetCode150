from typing import List


class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        m, n = len(matrix), len(matrix[0])
        zero_row, zero_col = [False] * m, [False] * n

        for i in range(m):
            for j in range(n):
                if matrix[i][j] == 0:
                    zero_row[i] = zero_col[j] = True

        for i in range(m):
            for j in range(n):
                if zero_row[i] or zero_col[j]:
                    matrix[i][j] = 0
