/**
 * @param {character[][]} board
 * @return {boolean}
 */
var isValidSudoku = function (board) {
  const seenRows = new Array(9).fill(0);
  const seenCols = new Array(9).fill(0);
  const seenBoxes = new Array(9).fill(0);

  const checkAndMark = (masks, idx, bit) => {
    if ((masks[idx] & (1 << bit)) !== 0) return false;
    masks[idx] |= 1 << bit;
    return true;
  };

  for (let i = 0; i < 9; i++) {
    for (let j = 0; j < 9; j++) {
      if (board[i][j] === ".") continue;

      const current = board[i][j].charCodeAt(0) - "0".charCodeAt(0) - 1;
      const box = Math.floor(i / 3) * 3 + Math.floor(j / 3);

      if (!checkAndMark(seenRows, i, current)) return false;
      if (!checkAndMark(seenCols, j, current)) return false;
      if (!checkAndMark(seenBoxes, box, current)) return false;
    }
  }

  return true;
};
