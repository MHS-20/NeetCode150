/**
 * @param {number[]} nums
 * @return {number[]}
 */
var productExceptSelf = function (nums) {
  const n = nums.length;
  const prefixes = new Array(n);
  const suffixes = new Array(n);
  const ans = new Array(n);

  prefixes[0] = 1;
  for (let i = 1; i < n; i++) prefixes[i] = prefixes[i - 1] * nums[i - 1];

  suffixes[n - 1] = 1;
  for (let i = n - 2; i >= 0; i--) suffixes[i] = suffixes[i + 1] * nums[i + 1];

  for (let i = 0; i < n; i++) ans[i] = prefixes[i] * suffixes[i];

  return ans;
};
