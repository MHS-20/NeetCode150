#include <stdlib.h>

static int min(int a, int b) { return a < b ? a : b; }

int minCostClimbingStairs(int *cost, int costSize) {
  int n = costSize;
  int *dp = malloc((n + 1) * sizeof(int));
  dp[0] = 0; // start on step 0 for free
  dp[1] = 0; // start on step 1 for free

  for (int i = 2; i <= n; i++) {
    dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
  }
  int res = dp[n]; // n = the top, one past the last step
  free(dp);
  return res;
}
