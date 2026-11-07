#include <stdlib.h>

int change(int amount, int *coins, int coinsSize) {
  int n = coinsSize, w = amount + 1;
  // dp[i * w + x]; unsigned so intermediate overflow wraps instead of being UB
  unsigned long long *dp = calloc((n + 1) * w, sizeof(unsigned long long));
  for (int i = 0; i <= n; i++)
    dp[i * w] = 1; // one way to make 0: use nothing

  for (int i = 1; i <= n; i++) {
    for (int x = 1; x <= amount; x++) {
      dp[i * w + x] = dp[(i - 1) * w + x]; // skip coin i
      if (coins[i - 1] <= x)
        dp[i * w + x] += dp[i * w + (x - coins[i - 1])]; // take coin i (same row)
    }
  }
  int res = (int)dp[n * w + amount];
  free(dp);
  return res;
}
