/**
 * @param {number[]} nums
 * @return {number[][]}
 */
var permute = function (nums) {
  const result = [];
  const cur = [...nums];

  const backtrack = (idx) => {
    if (idx === cur.length) {
      result.push([...cur]);
      return;
    }

    for (let i = idx; i < cur.length; i++) {
      [cur[idx], cur[i]] = [cur[i], cur[idx]];
      backtrack(idx + 1);
      [cur[idx], cur[i]] = [cur[i], cur[idx]];
    }
  };

  backtrack(0);
  return result;
};
