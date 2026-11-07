/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var topKFrequent = function (nums, k) {
  const freq = new Map();
  for (const n of nums) freq.set(n, (freq.get(n) || 0) + 1);

  const entries = Array.from(freq.entries());
  entries.sort((a, b) => b[1] - a[1]);

  return entries.slice(0, k).map((entry) => entry[0]);
};
