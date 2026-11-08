#include <stdbool.h>
#include <stdlib.h>

void setZeroes(int **matrix, int matrixSize, int *matrixColSize) {
  int m = matrixSize, n = matrixColSize[0];
  bool *zeroRow = calloc(m, sizeof(bool));
  bool *zeroCol = calloc(n, sizeof(bool));

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (matrix[i][j] == 0)
        zeroRow[i] = zeroCol[j] = true;

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (zeroRow[i] || zeroCol[j])
        matrix[i][j] = 0;

  free(zeroRow);
  free(zeroCol);
}
