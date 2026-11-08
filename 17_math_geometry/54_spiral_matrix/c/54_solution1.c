#include <stdlib.h>

int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize,
                 int *returnSize) {
  int top = 0, bottom = matrixSize - 1;
  int left = 0, right = matrixColSize[0] - 1;
  int *res = malloc(sizeof(int) * matrixSize * matrixColSize[0]);
  int k = 0;

  while (top <= bottom && left <= right) {
    for (int i = left; i <= right; i++)
      res[k++] = matrix[top][i];
    top++;

    for (int i = top; i <= bottom; i++)
      res[k++] = matrix[i][right];
    right--;

    if (top <= bottom) {
      for (int i = right; i >= left; i--)
        res[k++] = matrix[bottom][i];
      bottom--;
    }

    if (left <= right) {
      for (int i = bottom; i >= top; i--)
        res[k++] = matrix[i][left];
      left++;
    }
  }
  *returnSize = k;
  return res;
}
