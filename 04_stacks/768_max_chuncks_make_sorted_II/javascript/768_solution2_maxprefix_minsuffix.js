/**
 * @param {number[]} arr
 * @return {number}
 */
var maxChunksToSorted = function (arr) {
  const n = arr.length;
  const sufMin = new Array(n + 1).fill(Infinity);
  for (let i = n - 1; i >= 0; i--) sufMin[i] = Math.min(sufMin[i + 1], arr[i]);

  let chunks = 0;
  let prefMax = -Infinity;
  for (let i = 0; i < n; i++) {
    prefMax = Math.max(prefMax, arr[i]);
    if (prefMax <= sufMin[i + 1]) chunks++; // valid cut after i (i = n-1 always counts)
  }
  return chunks;
};
