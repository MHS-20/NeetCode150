/**
 * @param {number[]} nums
 * @return {boolean}
 */
var containsDuplicate = function (nums) {
  const tracker = new Set();

  for (const x of nums) {
    if (tracker.has(x)) {
      return true;
    }
    tracker.add(x);
  }

  return false;
};
