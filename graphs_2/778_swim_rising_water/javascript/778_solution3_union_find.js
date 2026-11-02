/**
 * @param {number[][]} grid
 * @return {number}
 */
var swimInWater = function (grid) {
  const n = grid.length;
  const parent = Array.from({ length: n * n }, (_, i) => i);
  const rnk = new Array(n * n).fill(0);

  const find = (x) => {
    while (parent[x] !== x) {
      parent[x] = parent[parent[x]]; // path halving
      x = parent[x];
    }
    return x;
  };

  const unite = (a, b) => {
    a = find(a);
    b = find(b);
    if (a === b) return;
    if (rnk[a] < rnk[b]) [a, b] = [b, a];
    parent[b] = a;
    if (rnk[a] === rnk[b]) rnk[a]++;
  };

  // pos[v] = cell index holding elevation v
  const pos = new Array(n * n);
  for (let r = 0; r < n; r++) for (let c = 0; c < n; c++) pos[grid[r][c]] = r * n + c;

  const dirs = [[1, 0], [-1, 0], [0, 1], [0, -1]];

  for (let t = 0; t < n * n; t++) {
    const r = Math.floor(pos[t] / n), c = pos[t] % n; // this cell becomes submerged
    for (const [dr, dc] of dirs) {
      const nr = r + dr, nc = c + dc;
      if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
      if (grid[nr][nc] <= t) unite(r * n + c, nr * n + nc); // neighbor already submerged
    }
    if (find(0) === find(n * n - 1)) return t;
  }
  return -1;
};
