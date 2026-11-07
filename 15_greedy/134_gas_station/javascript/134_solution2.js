/**
 * @param {number[]} gas
 * @param {number[]} cost
 * @return {number}
 */
var canCompleteCircuit = function (gas, cost) {
  let total = 0,
    cur = 0,
    start = 0;
  for (let i = 0; i < gas.length; i++) {
    const diff = gas[i] - cost[i];
    total += diff;
    cur += diff;
    if (cur < 0) {
      start = i + 1;
      cur = 0;
    }
  }
  return total < 0 ? -1 : start;
};
