/**
 * @param {number[]} nums
 * @return {number}
 */
var maxCoins = function (nums) {
  const a = [1, ...nums, 1]; // pad: [1, nums..., 1]

  const N = a.length;
  const dp = Array.from({ length: N }, () => new Array(N).fill(0)); // len < 2 → 0 already

  for (let len = 2; len < N; len++) {
    // distance between walls
    for (let l = 0; l + len < N; l++) {
      const r = l + len;
      for (let k = l + 1; k < r; k++) {
        dp[l][r] = Math.max(dp[l][r], dp[l][k] + dp[k][r] + a[l] * a[k] * a[r]);
      }
    }
  }
  return dp[0][N - 1];
};
