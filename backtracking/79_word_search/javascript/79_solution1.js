const DIRS = [
  [1, 0],
  [0, 1],
  [-1, 0],
  [0, -1],
];

/**
 * @param {character[][]} board
 * @param {string} word
 * @return {boolean}
 */
var exist = function (board, word) {
  const dfs = (idx, row, col) => {
    const ch = word[idx];
    if (ch !== board[row][col]) return false;

    if (idx === word.length - 1) return true;

    board[row][col] = "#";
    for (const [dr, dc] of DIRS) {
      const nr = row + dr,
        nc = col + dc;

      if (nr < 0 || nr >= board.length || nc < 0 || nc >= board[0].length)
        continue;

      if (dfs(idx + 1, nr, nc)) return true;
    }

    board[row][col] = ch;
    return false;
  };

  for (let r = 0; r < board.length; r++)
    for (let c = 0; c < board[0].length; c++) if (dfs(0, r, c)) return true;
  return false;
};
