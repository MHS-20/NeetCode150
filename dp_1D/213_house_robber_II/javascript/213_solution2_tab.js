/**
 * @param {number[]} nums
 * @return {number}
 */
var rob = function (nums) {
  const n = nums.length;
  if (n === 1) return nums[0];

  // Max loot from houses start..end (inclusive), in a straight line
  const robRange = (start, end) => {
    const len = end - start + 1;
    if (len === 1) return nums[start];

    const dp = new Array(len);
    dp[0] = nums[start];
    dp[1] = Math.max(nums[start], nums[start + 1]);

    for (let i = 2; i < len; i++) {
      dp[i] = Math.max(
        dp[i - 1], // skip this house
        dp[i - 2] + nums[start + i], // rob this house
      );
    }
    return dp[len - 1];
  };

  return Math.max(
    robRange(0, n - 2), // exclude the last house
    robRange(1, n - 1), // exclude the first house
  );
};
