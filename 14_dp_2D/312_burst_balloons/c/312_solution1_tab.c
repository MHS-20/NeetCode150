#include <stdlib.h>

int maxCoins(int *nums, int numsSize) {
  int N = numsSize + 2;
  int *a = malloc(N * sizeof(int)); // pad: [1, nums..., 1]
  a[0] = a[N - 1] = 1;
  for (int i = 0; i < numsSize; i++)
    a[i + 1] = nums[i];

  int *dp = calloc(N * N, sizeof(int)); // dp[l * N + r]; len < 2 → 0 already

  for (int len = 2; len < N; len++) { // distance between walls
    for (int l = 0; l + len < N; l++) {
      int r = l + len;
      for (int k = l + 1; k < r; k++) {
        int coins = dp[l * N + k] + dp[k * N + r] + a[l] * a[k] * a[r];
        if (coins > dp[l * N + r])
          dp[l * N + r] = coins;
      }
    }
  }
  int res = dp[N - 1];
  free(a);
  free(dp);
  return res;
}
