#include <stdlib.h>

int uniquePaths(int m, int n) {
  int *dp = calloc(m * n, sizeof(int)); // dp[i * n + j]: paths from (i, j)
  dp[(m - 1) * n + (n - 1)] = 1;

  for (int i = m - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--) {
      if (i == m - 1 && j == n - 1)
        continue;
      int down = (i + 1 < m) ? dp[(i + 1) * n + j] : 0;
      int right = (j + 1 < n) ? dp[i * n + (j + 1)] : 0;
      dp[i * n + j] = down + right;
    }
  }
  int res = dp[0];
  free(dp);
  return res;
}
