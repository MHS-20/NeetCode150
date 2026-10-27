const find = (parent, x) => {
  while (parent[x] !== x) x = parent[x];
  return x;
};

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {boolean}
 */
var validTree = function (n, edges) {
  let count = n;
  const parent = Array.from({ length: n + 1 }, (_, i) => i);

  for (const [a, b] of edges) {
    const ra = find(parent, a);
    const rb = find(parent, b);
    if (ra === rb) return false;
    count--;
    parent[rb] = ra;
  }
  return count === 1;
};
