class Solution:
    def searchMatrix(self, matrix: list[list[int]], target: int) -> bool:
        rows, cols = len(matrix), len(matrix[0])
        left, right = 0, rows * cols - 1

        while left <= right:
            mid = left + (right - left) // 2
            i, j = divmod(mid, cols)

            if matrix[i][j] == target:
                return True
            if matrix[i][j] > target:
                right = mid - 1
            else:
                left = mid + 1
        return False
