#include <stdlib.h>

static int solve(int i, int j, int n, int *dp) {
  if (i == 0 && j == 0)
    return 1; // reached the start
  if (i < 0 || j < 0)
    return 0; // fell off the grid
  if (dp[i * n + j] != -1)
    return dp[i * n + j]; // already computed

  int up = solve(i - 1, j, n, dp);
  int left = solve(i, j - 1, n, dp);
  return dp[i * n + j] = up + left;
}

int uniquePaths(int m, int n) {
  int *dp = malloc(m * n * sizeof(int)); // dp[i * n + j]
  for (int k = 0; k < m * n; k++)
    dp[k] = -1;
  int res = solve(m - 1, n - 1, n, dp);
  free(dp);
  return res;
}
