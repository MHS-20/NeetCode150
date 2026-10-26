const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

/**
 * @param {character[][]} board
 * @return {void} Do not return anything, modify board in-place instead.
 */
var solve = function (board) {
  const rows = board.length,
    cols = board[0].length;

  const dfs = (r, c) => {
    if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] !== "O") return;
    board[r][c] = ".";
    for (const [dr, dc] of DIRS) dfs(r + dr, c + dc);
  };

  // 1. mark border-connected 'O's as safe
  for (let i = 0; i < rows; i++) {
    dfs(i, 0);
    dfs(i, cols - 1);
  }
  for (let j = 0; j < cols; j++) {
    dfs(0, j);
    dfs(rows - 1, j);
  }

  // 2. capture leftover 'O's, restore safe ones
  for (const row of board)
    for (let j = 0; j < cols; j++) {
      if (row[j] === "O") row[j] = "X";
      else if (row[j] === ".") row[j] = "O";
    }
};
