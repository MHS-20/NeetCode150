#include <stdlib.h>

static int max(int a, int b) { return a > b ? a : b; }

int lengthOfLIS(int *nums, int numsSize) {
  int n = numsSize;
  int *dp = malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    dp[i] = 1;
  int best = 1;

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (nums[j] < nums[i])
        dp[i] = max(dp[i], dp[j] + 1);
    }
    best = max(best, dp[i]);
  }
  free(dp);
  return best;
}
