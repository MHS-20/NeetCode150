/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var permute = function (nums) {
  const result = [];

  const backtrack = (idx, i) => {
    if (idx === nums.length) {
      result.push([...nums]);
      return;
    }
    if (i === nums.length) return;

    // choose nums[i] for position idx, then fix the next position
    [nums[idx], nums[i]] = [nums[i], nums[idx]];
    backtrack(idx + 1, idx + 1);
    [nums[idx], nums[i]] = [nums[i], nums[idx]]; // undo

    // try the next candidate for the same position
    backtrack(idx, i + 1);
  };

  backtrack(0, 0);
  return result;
};
