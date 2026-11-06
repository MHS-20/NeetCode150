#include <stdlib.h>

int coinChange(int *coins, int coinsSize, int amount) {
  int INF = amount + 1;
  int *dp = malloc((amount + 1) * sizeof(int));
  dp[0] = 0;
  for (int x = 1; x <= amount; x++)
    dp[x] = INF;

  for (int x = 1; x <= amount; x++) {
    for (int k = 0; k < coinsSize; k++) {
      int c = coins[k];
      if (c <= x && dp[x - c] != INF && dp[x - c] + 1 < dp[x]) {
        dp[x] = dp[x - c] + 1;
      }
    }
  }
  int res = dp[amount] == INF ? -1 : dp[amount];
  free(dp);
  return res;
}
