/**
 * @param {number[]} gas
 * @param {number[]} cost
 * @return {number}
 */
var canCompleteCircuit = function (gas, cost) {
  const sumGas = gas.reduce((a, b) => a + b, 0);
  const sumCost = cost.reduce((a, b) => a + b, 0);
  if (sumCost > sumGas) return -1;

  let start = 0,
    curGas = 0,
    curPos = 0;
  for (;;) {
    curGas += gas[curPos] - cost[curPos];

    curPos = (curPos + 1) % gas.length;

    if (curPos === start) return start;

    if (curGas < 0) {
      start = curPos;
      curGas = 0;
    }
  }
};
