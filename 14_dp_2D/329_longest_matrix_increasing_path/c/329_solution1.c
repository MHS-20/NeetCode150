#include <stdlib.h>

static int m, n;
static int **mat;
static int *dp; // dp[i * n + j], 0 = not computed
static const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

static int max(int a, int b) { return a > b ? a : b; }

static int dfs(int i, int j) {
  if (dp[i * n + j] != 0)
    return dp[i * n + j]; // already computed

  int best = 1; // the cell alone
  for (int d = 0; d < 4; d++) {
    int ni = i + dirs[d][0], nj = j + dirs[d][1];
    if (ni >= 0 && ni < m && nj >= 0 && nj < n && mat[ni][nj] > mat[i][j]) {
      best = max(best, 1 + dfs(ni, nj));
    }
  }
  return dp[i * n + j] = best;
}

int longestIncreasingPath(int **matrix, int matrixSize, int *matrixColSize) {
  m = matrixSize;
  n = matrixColSize[0];
  mat = matrix;
  dp = calloc(m * n, sizeof(int));

  int res = 0;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      res = max(res, dfs(i, j));
  free(dp);
  return res;
}
