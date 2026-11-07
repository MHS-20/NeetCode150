/**
 * @param {number} amount
 * @param {number[]} coins
 * @return {number}
 */
var change = function (amount, coins) {
  const n = coins.length;
  const dp = Array.from({ length: n + 1 }, () => new Array(amount + 1).fill(0));
  for (let i = 0; i <= n; i++) dp[i][0] = 1; // one way to make 0: use nothing

  for (let i = 1; i <= n; i++) {
    for (let x = 1; x <= amount; x++) {
      dp[i][x] = dp[i - 1][x]; // skip coin i
      if (coins[i - 1] <= x) dp[i][x] += dp[i][x - coins[i - 1]]; // take coin i (same row)
    }
  }
  return dp[n][amount];
};
