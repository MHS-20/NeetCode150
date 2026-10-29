/**
 * @param {number[][]} intervals
 * @return {number[][]}
 */
var merge = function (intervals) {
  intervals.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
  const result = [];

  for (const cur of intervals) {
    const last = result[result.length - 1];
    if (!last || last[1] < cur[0]) result.push(cur);
    else last[1] = Math.max(last[1], cur[1]);
  }

  return result;
};
