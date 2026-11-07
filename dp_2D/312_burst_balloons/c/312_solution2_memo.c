#include <stdlib.h>

static int *a, *dp, N; // dp[l * N + r], -1 = not computed

static int f(int l, int r) {
  if (r - l < 2)
    return 0; // nothing strictly between l and r
  if (dp[l * N + r] != -1)
    return dp[l * N + r];

  int best = 0;
  for (int k = l + 1; k < r; k++) { // k = last balloon burst in (l, r)
    int coins = a[l] * a[k] * a[r] + f(l, k) + f(k, r);
    if (coins > best)
      best = coins;
  }
  return dp[l * N + r] = best;
}

int maxCoins(int *nums, int numsSize) {
  N = numsSize + 2;
  a = malloc(N * sizeof(int)); // pad: [1, nums..., 1]
  a[0] = a[N - 1] = 1;
  for (int i = 0; i < numsSize; i++)
    a[i + 1] = nums[i];

  dp = malloc(N * N * sizeof(int));
  for (int k = 0; k < N * N; k++)
    dp[k] = -1;
  int res = f(0, N - 1);
  free(a);
  free(dp);
  return res;
}
