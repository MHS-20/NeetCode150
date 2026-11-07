/**
 * @param {number[]} nums
 * @return {number}
 */
var rob = function (nums) {
  const memo = new Array(nums.length).fill(-1);

  const maxLoot = (idx) => {
    if (idx === 0) return nums[0];
    if (idx === 1) return Math.max(nums[0], nums[1]);

    if (memo[idx] !== -1) return memo[idx];

    return (memo[idx] = Math.max(
      maxLoot(idx - 1), // skip this house
      maxLoot(idx - 2) + nums[idx], // rob this house
    ));
  };

  return maxLoot(nums.length - 1);
};
