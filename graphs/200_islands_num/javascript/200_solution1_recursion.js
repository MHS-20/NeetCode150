const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

const sink = (grid, r, c, rows, cols) => {
  if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] !== "1") return;
  grid[r][c] = "0";
  for (const [dr, dc] of DIRS) sink(grid, r + dr, c + dc, rows, cols);
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
