/**
 * @param {number} n
 * @return {string[][]}
 */
var solveNQueens = function (n) {
  const result = [];
  const board = Array.from({ length: n }, () => Array(n).fill("."));
  const cols = Array(n).fill(false);
  const diag1 = Array(2 * n - 1).fill(false);
  const diag2 = Array(2 * n - 1).fill(false);

  const backtrack = (row) => {
    if (row === n) {
      result.push(board.map((r) => r.join("")));
      return;
    }

    for (let col = 0; col < n; col++) {
      const d1 = row + col; // "/" diagonal
      const d2 = row - col + n - 1; // "\" diagonal, shifted
      if (cols[col] || diag1[d1] || diag2[d2]) continue;

      board[row][col] = "Q";
      cols[col] = diag1[d1] = diag2[d2] = true;

      backtrack(row + 1);

      board[row][col] = ".";
      cols[col] = diag1[d1] = diag2[d2] = false;
    }
  };

  backtrack(0);
  return result;
};
