#include <stdbool.h>
#include <stdlib.h>

bool canPartition(int *nums, int numsSize) {
  int total = 0;
  for (int i = 0; i < numsSize; i++)
    total += nums[i];
  if (total % 2 != 0)
    return false;
  int target = total / 2;

  bool *dp = calloc(target + 1, sizeof(bool));
  dp[0] = true;

  for (int i = 0; i < numsSize; i++) {
    int x = nums[i];
    // Go backward so each number is used at most once
    for (int s = target; s >= x; s--) {
      if (dp[s - x])
        dp[s] = true;
    }
  }
  bool res = dp[target];
  free(dp);
  return res;
}
