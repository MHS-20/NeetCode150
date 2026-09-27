#include <stdbool.h>

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target) {
    int rows = matrixSize, cols = matrixColSize[0];
    int left = 0, right = rows * cols - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int i = mid / cols, j = mid % cols;

        if (matrix[i][j] == target)
            return true;
        if (matrix[i][j] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return false;
}
