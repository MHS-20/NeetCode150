const find = (parent, x) => {
  while (parent[x] !== x) x = parent[x];
  return x;
};

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countComponents = function (n, edges) {
  const parent = Array.from({ length: n + 1 }, (_, i) => i);
  let count = n;

  for (const [a, b] of edges) {
    const ra = find(parent, a);
    const rb = find(parent, b);
    if (ra !== rb) count--;
    parent[rb] = ra;
  }
  return count;
};
