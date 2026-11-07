#include <stdlib.h>

static int *nums_, n_, tot_, target_, w_;
static int *dp; // dp[i * w_ + (sum + tot_)], -1 = not computed

// Ways to reach target using nums[i..], given the running sum so far
static int f(int i, int sum) {
  if (i == n_)
    return sum == target_ ? 1 : 0;
  if (dp[i * w_ + (sum + tot_)] != -1)
    return dp[i * w_ + (sum + tot_)];

  int add = f(i + 1, sum + nums_[i]); // +nums[i]
  int sub = f(i + 1, sum - nums_[i]); // -nums[i]
  return dp[i * w_ + (sum + tot_)] = add + sub;
}

int findTargetSumWays(int *nums, int numsSize, int target) {
  int tot = 0;
  for (int i = 0; i < numsSize; i++)
    tot += nums[i];
  if (abs(target) > tot)
    return 0;

  nums_ = nums, n_ = numsSize, tot_ = tot, target_ = target, w_ = 2 * tot + 1;
  dp = malloc(n_ * w_ * sizeof(int));
  for (int k = 0; k < n_ * w_; k++)
    dp[k] = -1;
  int res = f(0, 0);
  free(dp);
  return res;
}
