/**
 * @param {number[]} hand
 * @param {number} groupSize
 * @return {boolean}
 */
var isNStraightHand = function (hand, groupSize) {
  if (hand.length % groupSize !== 0) return false;

  const count = new Map();
  for (const c of hand) count.set(c, (count.get(c) ?? 0) + 1);

  // ascending, so each value is the smallest remaining card when reached
  const keys = [...count.keys()].sort((a, b) => a - b);
  for (const start of keys) {
    const c = count.get(start);
    if (c === 0) continue; // already used up by earlier groups
    for (let v = start; v < start + groupSize; v++) {
      if ((count.get(v) ?? 0) < c) return false; // missing value, group can't be built
      count.set(v, count.get(v) - c);
    }
  }

  return true;
};
