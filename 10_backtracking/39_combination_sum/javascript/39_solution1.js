/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum = function (candidates, target) {
  const result = [];
  const cur = [];

  const backtrack = (idx, sum) => {
    if (sum === target) {
      result.push([...cur]);
      return;
    }
    if (sum > target || idx >= candidates.length) return;

    // include candidates[idx], stay on idx (can reuse it)
    cur.push(candidates[idx]);
    backtrack(idx, sum + candidates[idx]);
    cur.pop();

    // skip candidates[idx] for good, move on
    backtrack(idx + 1, sum);
  };

  backtrack(0, 0);
  return result;
};
