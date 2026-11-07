/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var topKFrequent = function (nums, k) {
  const freq = new Map();
  for (const n of nums) freq.set(n, (freq.get(n) || 0) + 1);

  const buckets = Array.from({ length: nums.length + 1 }, () => []);
  for (const [val, cnt] of freq.entries()) buckets[cnt].push(val);

  const res = [];
  for (let i = buckets.length - 1; i >= 0 && res.length < k; i--) {
    for (const val of buckets[i]) {
      res.push(val);
      if (res.length === k) break;
    }
  }

  return res;
};
