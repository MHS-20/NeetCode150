/**
 * @param {number[]} nums
 * @return {number}
 */
var maxCoins = function (nums) {
  const a = [1, ...nums, 1]; // pad: [1, nums..., 1]

  const N = a.length;
  const dp = Array.from({ length: N }, () => new Array(N).fill(-1));

  const f = (l, r) => {
    if (r - l < 2) return 0; // nothing strictly between l and r
    if (dp[l][r] !== -1) return dp[l][r];

    let best = 0;
    for (let k = l + 1; k < r; k++) {
      // k = last balloon burst in (l, r)
      const coins = a[l] * a[k] * a[r] + f(l, k) + f(k, r);
      best = Math.max(best, coins);
    }
    return (dp[l][r] = best);
  };

  return f(0, N - 1);
};
