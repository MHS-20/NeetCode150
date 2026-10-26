const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

/**
 * @param {number[][]} heights
 * @return {number[][]}
 */
var pacificAtlantic = function (heights) {
  const rows = heights.length,
    cols = heights[0].length;
  const newGrid = () => Array.from({ length: rows }, () => Array(cols).fill(false));
  const pacific = newGrid(),
    atlantic = newGrid();

  const dfs = (ocean, r, c, prevHeight) => {
    if (r < 0 || c < 0 || r >= rows || c >= cols) return;
    if (ocean[r][c] || heights[r][c] < prevHeight) return;

    ocean[r][c] = true;
    for (const [dr, dc] of DIRS) dfs(ocean, r + dr, c + dc, heights[r][c]);
  };

  for (let i = 0; i < rows; i++) {
    dfs(pacific, i, 0, -Infinity);
    dfs(atlantic, i, cols - 1, -Infinity);
  }
  for (let j = 0; j < cols; j++) {
    dfs(pacific, 0, j, -Infinity);
    dfs(atlantic, rows - 1, j, -Infinity);
  }

  const result = [];
  for (let i = 0; i < rows; i++)
    for (let j = 0; j < cols; j++) if (pacific[i][j] && atlantic[i][j]) result.push([i, j]);
  return result;
};
