/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var subsetsWithDup = function (nums) {
  const result = [];
  const cur = [];
  nums.sort((a, b) => a - b);

  const backtrack = (idx) => {
    if (idx === nums.length) {
      result.push([...cur]);
      return;
    }

    cur.push(nums[idx]);
    backtrack(idx + 1);
    cur.pop();

    let i = idx + 1;
    while (i < nums.length && nums[idx] === nums[i]) i++;

    backtrack(i);
  };

  backtrack(0);
  return result;
};
