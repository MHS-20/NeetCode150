void rotate(int **matrix, int matrixSize, int *matrixColSize) {
  int n = matrixSize;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int tmp = matrix[j][i];
      matrix[j][i] = matrix[i][j];
      matrix[i][j] = tmp;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n / 2; j++) {
      int tmp = matrix[i][n - j - 1];
      matrix[i][n - j - 1] = matrix[i][j];
      matrix[i][j] = tmp;
    }
  }
}
