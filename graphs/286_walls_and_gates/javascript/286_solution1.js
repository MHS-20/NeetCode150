const INF = 2147483647;
const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

/**
 * @param {number[][]} grid
 */
var islandsAndTreasure = function (grid) {
  const rows = grid.length,
    cols = grid[0].length;
  const q = [];

  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++) if (grid[i][j] === 0) q.push([i, j]);

  // index-based queue: Array.shift() is O(n)
  for (let head = 0; head < q.length; head++) {
    const [r, c] = q[head];
    for (const [dr, dc] of DIRS) {
      const nr = r + dr,
        nc = c + dc;
      if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
      if (grid[nr][nc] !== INF) continue;

      grid[nr][nc] = grid[r][c] + 1;
      q.push([nr, nc]);
    }
  }
};
