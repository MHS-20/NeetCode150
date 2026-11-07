/**
 * @param {number[][]} intervals
 * @param {number[]} newInterval
 * @return {number[][]}
 */
var insert = function (intervals, newInterval) {
  const result = [];
  let i = 0;
  const n = intervals.length;

  // 1. Intervals entirely before newInterval
  while (i < n && intervals[i][1] < newInterval[0]) result.push(intervals[i++]);

  // 2. Intervals overlapping newInterval: absorb them into it
  while (i < n && intervals[i][0] <= newInterval[1]) {
    newInterval[0] = Math.min(newInterval[0], intervals[i][0]);
    newInterval[1] = Math.max(newInterval[1], intervals[i][1]);
    i++;
  }
  result.push(newInterval);

  // 3. Intervals entirely after newInterval
  while (i < n) result.push(intervals[i++]);

  return result;
};
