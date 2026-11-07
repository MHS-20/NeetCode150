#include <stdlib.h>

int uniquePaths(int m, int n) {
  int *dp = calloc(m * n, sizeof(int)); // dp[i * n + j]

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i == 0 && j == 0) {
        dp[0] = 1;
        continue;
      }
      int up = (i > 0) ? dp[(i - 1) * n + j] : 0;
      int left = (j > 0) ? dp[i * n + (j - 1)] : 0;
      dp[i * n + j] = up + left;
    }
  }
  int res = dp[(m - 1) * n + (n - 1)];
  free(dp);
  return res;
}
