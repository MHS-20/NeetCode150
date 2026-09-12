/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var topKFrequent = function (nums, k) {
  const freq = new Map();
  for (const n of nums) freq.set(n, (freq.get(n) || 0) + 1);

  const maxHeap = Array.from(freq.entries());
  maxHeap.sort((a, b) => b[1] - a[1]);

  const res = [];
  for (let i = 0; i < k; i++) res.push(maxHeap[i][0]);
  return res;
};
