/**
 * @param {number[]} nums
 * @return {number}
 */
var maxProduct = function (nums) {
  let curMax = nums[0], curMin = nums[0], best = nums[0];

  for (let i = 1; i < nums.length; i++) {
    const x = nums[i];
    const a = curMax * x, b = curMin * x;

    curMax = Math.max(x, a, b);
    curMin = Math.min(x, a, b);
    best = Math.max(best, curMax);
  }
  return best;
};
