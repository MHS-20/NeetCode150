/**
 * @param {number[]} candidates
 * @param {number} target
 * @return {number[][]}
 */
var combinationSum2 = function (candidates, target) {
  const result = [];
  const cur = [];
  candidates.sort((a, b) => a - b);

  const backtrack = (idx, sum) => {
    if (sum === target) {
      result.push([...cur]);
      return;
    }

    if (sum > target || idx === candidates.length) return;

    cur.push(candidates[idx]);
    backtrack(idx + 1, sum + candidates[idx]);
    cur.pop();

    let i = idx + 1;
    while (i < candidates.length && candidates[i] === candidates[idx]) i++;
    backtrack(i, sum);
  };

  backtrack(0, 0);
  return result;
};
