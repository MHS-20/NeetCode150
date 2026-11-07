#include <stdlib.h>

static int f(int i, int x, int *coins, int n, int w, unsigned *dp) {
  if (x == 0)
    return 1; // made the amount
  if (i == n)
    return 0; // out of coins
  if (dp[i * w + x] != (unsigned)-1)
    return dp[i * w + x];

  unsigned skip = f(i + 1, x, coins, n, w, dp); // never use coin i again
  unsigned take = 0;
  if (coins[i] <= x)
    take = f(i, x - coins[i], coins, n, w,
             dp); // use coin i, stay at i (reuse allowed)

  // unsigned so intermediate overflow wraps instead of being UB
  return dp[i * w + x] = skip + take;
}

int change(int amount, int *coins, int coinsSize) {
  int w = amount + 1;
  unsigned *dp = malloc(coinsSize * w * sizeof(unsigned)); // dp[i * w + x]
  for (int k = 0; k < coinsSize * w; k++)
    dp[k] = (unsigned)-1;
  int res = f(0, amount, coins, coinsSize, w, dp);
  free(dp);
  return res;
}
