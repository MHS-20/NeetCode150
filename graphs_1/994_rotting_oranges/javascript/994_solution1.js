const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

/**
 * @param {number[][]} grid
 * @return {number}
 */
var orangesRotting = function (grid) {
  const rows = grid.length,
    cols = grid[0].length;
  let q = [];
  let fresh = 0;

  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++) {
      if (grid[i][j] === 2) q.push([i, j]);
      else if (grid[i][j] === 1) fresh++;
    }

  let minutes = 0;
  while (q.length > 0 && fresh > 0) {
    // swap in a fresh array per level: Array.shift() is O(n)
    const next = [];
    minutes++;
    for (const [r, c] of q) {
      for (const [dr, dc] of DIRS) {
        const nr = r + dr,
          nc = c + dc;
        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols) continue;
        if (grid[nr][nc] !== 1) continue;

        grid[nr][nc] = 2;
        fresh--;
        next.push([nr, nc]);
      }
    }
    q = next;
  }
  return fresh === 0 ? minutes : -1;
};
