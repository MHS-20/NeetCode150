/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var subsets = function (nums) {
  const result = [];
  const cur = [];

  const backtrack = (idx) => {
    if (idx === nums.length) {
      result.push([...cur]);
      return;
    }
    // include nums[idx]
    cur.push(nums[idx]);
    backtrack(idx + 1);
    cur.pop(); // undo

    // skip nums[idx]
    backtrack(idx + 1);
  };

  backtrack(0);
  return result;
};
