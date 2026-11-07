#include <stdlib.h>

int findTargetSumWays(int *nums, int numsSize, int target) {
  int n = numsSize;
  int tot = 0;
  for (int i = 0; i < n; i++)
    tot += nums[i];
  if (abs(target) > tot)
    return 0;

  int w = 2 * tot + 1;
  int *dp = calloc((n + 1) * w, sizeof(int)); // dp[i * w + (s + tot)]
  dp[0 * w + (0 + tot)] = 1;                  // 0 numbers used, sum 0

  for (int i = 1; i <= n; i++) {
    int x = nums[i - 1];
    for (int s = -tot; s <= tot; s++) {
      int ways = 0;
      if (s - x >= -tot)
        ways += dp[(i - 1) * w + (s - x + tot)]; // added x
      if (s + x <= tot)
        ways += dp[(i - 1) * w + (s + x + tot)]; // subtracted x
      dp[i * w + (s + tot)] = ways;
    }
  }
  int res = dp[n * w + (target + tot)];
  free(dp);
  return res;
}
