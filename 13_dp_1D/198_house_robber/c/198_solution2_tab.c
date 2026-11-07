#include <stdlib.h>

static int max(int a, int b) { return a > b ? a : b; }

int rob(int *nums, int numsSize) {
  int n = numsSize;
  if (n == 1)
    return nums[0];

  int *dp = malloc(n * sizeof(int));
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);

  for (int i = 2; i < n; i++) {
    dp[i] = max(dp[i - 1],            // skip house i
                dp[i - 2] + nums[i]); // rob house i
  }
  int res = dp[n - 1];
  free(dp);
  return res;
}
