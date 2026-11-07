#include <stdlib.h>

static int max(int a, int b) { return a > b ? a : b; }

int maxProfit(int *prices, int pricesSize) {
  int n = pricesSize;
  int(*dp)[2] = calloc(n + 2, sizeof *dp); // dp[day][canBuy]

  for (int day = n - 1; day >= 0; day--) {
    // canBuy = 1
    dp[day][1] = max(-prices[day] + dp[day + 1][0], // buy
                     dp[day + 1][1]);               // skip
    // canBuy = 0 (holding)
    dp[day][0] = max(prices[day] + dp[day + 2][1], // sell + cooldown
                     dp[day + 1][0]);              // hold
  }
  int res = dp[0][1];
  free(dp);
  return res;
}
