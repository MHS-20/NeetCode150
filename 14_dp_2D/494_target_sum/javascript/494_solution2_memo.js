/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var findTargetSumWays = function (nums, target) {
  const n = nums.length;
  const tot = nums.reduce((a, b) => a + b, 0);
  if (Math.abs(target) > tot) return 0;

  // dp[i][sum + tot], -1 = not computed
  const dp = Array.from({ length: n }, () => new Array(2 * tot + 1).fill(-1));

  // Ways to reach target using nums[i..], given the running sum so far
  const f = (i, sum) => {
    if (i === n) return sum === target ? 1 : 0;
    if (dp[i][sum + tot] !== -1) return dp[i][sum + tot];

    const add = f(i + 1, sum + nums[i]); // +nums[i]
    const sub = f(i + 1, sum - nums[i]); // -nums[i]
    return (dp[i][sum + tot] = add + sub);
  };

  return f(0, 0);
};
