/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var findTargetSumWays = function (nums, target) {
  const n = nums.length;
  const tot = nums.reduce((a, b) => a + b, 0);
  if (Math.abs(target) > tot) return 0;

  const dp = Array.from({ length: n + 1 }, () => new Array(2 * tot + 1).fill(0));
  dp[0][0 + tot] = 1; // 0 numbers used, sum 0

  for (let i = 1; i <= n; i++) {
    const x = nums[i - 1];
    for (let s = -tot; s <= tot; s++) {
      let ways = 0;
      if (s - x >= -tot) ways += dp[i - 1][s - x + tot]; // added x
      if (s + x <= tot) ways += dp[i - 1][s + x + tot]; // subtracted x
      dp[i][s + tot] = ways;
    }
  }
  return dp[n][target + tot];
};
