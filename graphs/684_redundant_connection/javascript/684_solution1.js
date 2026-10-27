const find = (parent, x) => {
  while (parent[x] !== x) x = parent[x];
  return x;
};

/**
 * @param {number[][]} edges
 * @return {number[]}
 */
var findRedundantConnection = function (edges) {
  const n = edges.length;
  const parent = Array.from({ length: n + 1 }, (_, i) => i);

  for (const edge of edges) {
    const ra = find(parent, edge[0]);
    const rb = find(parent, edge[1]);
    if (ra === rb) return edge;
    parent[rb] = ra;
  }
  return [];
};
