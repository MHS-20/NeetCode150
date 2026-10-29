/**
 * @param {number[][]} intervals
 * @return {number}
 */
var eraseOverlapIntervals = function (intervals) {
  intervals.sort((a, b) => a[0] - b[0] || a[1] - b[1]);
  let kept = 0;
  let lastEnd = 0; // end of the last kept interval

  for (const [start, end] of intervals) {
    if (kept === 0 || lastEnd <= start) {
      kept++;
      lastEnd = end;
    } else if (lastEnd > end) {
      lastEnd = end; // overlap: keep the one that ends earlier
    }
  }

  return intervals.length - kept;
};
