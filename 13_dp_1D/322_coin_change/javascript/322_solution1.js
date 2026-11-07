/**
 * @param {number[]} coins
 * @param {number} amount
 * @return {number}
 */
var coinChange = function (coins, amount) {
  const INF = amount + 1;
  const dp = new Array(amount + 1).fill(INF);
  dp[0] = 0;

  for (let x = 1; x <= amount; x++) {
    for (const c of coins) {
      if (c <= x && dp[x - c] !== INF) {
        dp[x] = Math.min(dp[x], dp[x - c] + 1);
      }
    }
  }
  return dp[amount] === INF ? -1 : dp[amount];
};
