/**
 * @param {number[]} nums
 * @return {number}
 */
var maxSubArray = function (nums) {
  let sum = 0;
  let mx = -Infinity;

  for (const n of nums) {
    sum += n;
    mx = Math.max(sum, mx);
    if (sum < 0) sum = n < 0 ? 0 : n;
  }

  return mx;
};
