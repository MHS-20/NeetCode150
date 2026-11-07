#include <stdlib.h>

int change(int amount, int *coins, int coinsSize) {
  // unsigned so intermediate overflow wraps instead of being UB
  unsigned long long *dp = calloc(amount + 1, sizeof(unsigned long long));
  dp[0] = 1;
  for (int k = 0; k < coinsSize; k++) {
    int c = coins[k];
    for (int x = c; x <= amount; x++)
      dp[x] += dp[x - c];
  }
  int res = (int)dp[amount];
  free(dp);
  return res;
}
