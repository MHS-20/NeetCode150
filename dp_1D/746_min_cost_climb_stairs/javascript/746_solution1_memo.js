/**
 * @param {number[]} cost
 * @return {number}
 */
var minCostClimbingStairs = function (cost) {
  const memo = new Array(cost.length + 1).fill(-1);

  const costs = (i) => {
    if (i <= 1) return 0; // start on step 0 or 1 for free
    if (memo[i] !== -1) return memo[i];
    return (memo[i] = Math.min(
      costs(i - 1) + cost[i - 1],
      costs(i - 2) + cost[i - 2],
    ));
  };

  return costs(cost.length);
};
