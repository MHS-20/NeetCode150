/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var subsets = function (nums) {
  const result = [];
  const cur = [];

  const backtrack = (start) => {
    result.push([...cur]); // every path is a valid subset

    for (let i = start; i < nums.length; i++) {
      cur.push(nums[i]);
      backtrack(i + 1);
      cur.pop(); // undo
    }
  };

  backtrack(0);
  return result;
};
