/**
 * @param {number[]} nums
 * @return {number}
 */
var rob = function (nums) {
  const n = nums.length;
  if (n === 1) return nums[0];

  let memo;
  const maxLoot = (idx, start) => {
    if (idx < start) return 0;
    if (memo[idx] !== -1) return memo[idx];
    return (memo[idx] = Math.max(
      maxLoot(idx - 1, start),
      maxLoot(idx - 2, start) + nums[idx],
    ));
  };

  memo = new Array(n).fill(-1);
  const skipLast = maxLoot(n - 2, 0);

  memo = new Array(n).fill(-1); // reset: different subproblem
  const skipFirst = maxLoot(n - 1, 1);

  return Math.max(skipLast, skipFirst);
};
