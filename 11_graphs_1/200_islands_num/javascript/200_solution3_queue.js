const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

const sink = (grid, r, c, rows, cols) => {
  // index-based queue: Array.shift() is O(n)
  const q = [[r, c]];
  grid[r][c] = "0";
  for (let head = 0; head < q.length; head++) {
    const [cr, cc] = q[head];
    for (const [dr, dc] of DIRS) {
      const nr = cr + dr,
        nc = cc + dc;
      if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && grid[nr][nc] === "1") {
        grid[nr][nc] = "0";
        q.push([nr, nc]);
      }
    }
  }
};

/**
 * @param {character[][]} grid
 * @return {number}
 */
var numIslands = function (grid) {
  if (grid.length === 0) return 0;
  const rows = grid.length,
    cols = grid[0].length;
  let count = 0;
  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++)
      if (grid[i][j] === "1") {
        sink(grid, i, j, rows, cols);
        count++;
      }
  return count;
};
