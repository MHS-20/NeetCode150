/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var topKFrequent = function (nums, k) {
  const freq = new Map();
  for (const n of nums) freq.set(n, (freq.get(n) || 0) + 1);

  const minHeap = [];
  for (const [val, cnt] of freq.entries()) {
    minHeap.push([cnt, val]);
    minHeap.sort((a, b) => a[0] - b[0]);
    if (minHeap.length > k) minHeap.shift();
  }

  return minHeap.map((entry) => entry[1]);
};
