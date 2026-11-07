/**
 * @param {character[][]} board
 * @return {boolean}
 */
var isValidSudoku = function (board) {
  const seenRows = Array.from({ length: 9 }, () => new Array(9).fill(false));
  const seenCols = Array.from({ length: 9 }, () => new Array(9).fill(false));
  const seenBoxes = Array.from({ length: 9 }, () => new Array(9).fill(false));

  const checkAndMark = (arr, idx) => {
    if (arr[idx]) return false;
    arr[idx] = true;
    return true;
  };

  for (let i = 0; i < 9; i++) {
    for (let j = 0; j < 9; j++) {
      if (board[i][j] === ".") continue;

      const current = board[i][j].charCodeAt(0) - "0".charCodeAt(0) - 1;
      const box = Math.floor(i / 3) * 3 + Math.floor(j / 3);

      if (!checkAndMark(seenRows[i], current)) return false;
      if (!checkAndMark(seenCols[j], current)) return false;
      if (!checkAndMark(seenBoxes[box], current)) return false;
    }
  }

  return true;
};
