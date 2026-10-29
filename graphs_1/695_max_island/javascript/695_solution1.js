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
var maxAreaOfIsland = function (grid) {
  if (grid.length === 0) return 0;

  let mx = 0,
    count = 0;
  const rows = grid.length,
    cols = grid[0].length;

  const sink = (r, c) => {
    if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] !== 1) return;
    grid[r][c] = 0;
    count++;
    for (const [dr, dc] of DIRS) sink(r + dr, c + dc);
  };

  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++)
      if (grid[i][j] === 1) {
        count = 0;
        sink(i, j);
        mx = Math.max(count, mx);
      }
  return mx;
};
