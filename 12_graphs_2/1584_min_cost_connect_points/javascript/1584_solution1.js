/**
 * @param {number[][]} points
 * @return {number}
 */
var minCostConnectPoints = function (points) {
  const n = points.length;
  const minCost = new Array(n).fill(Infinity);
  const inTree = new Array(n).fill(false);
  minCost[0] = 0;
  let cost = 0;

  for (let step = 0; step < n; step++) {
    // 1. Pick the cheapest point not yet in the tree
    let u = -1;
    for (let i = 0; i < n; i++)
      if (!inTree[i] && (u === -1 || minCost[i] < minCost[u])) u = i;

    // 2. Add it
    inTree[u] = true;
    cost += minCost[u];

    // 3. Update the outside points' best connection
    for (let i = 0; i < n; i++) {
      if (inTree[i]) continue;
      const dist = Math.abs(points[i][0] - points[u][0]) + Math.abs(points[i][1] - points[u][1]);
      minCost[i] = Math.min(minCost[i], dist);
    }
  }
  return cost;
};
