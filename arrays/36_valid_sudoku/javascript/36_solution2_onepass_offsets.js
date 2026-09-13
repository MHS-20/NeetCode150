/**
 * @param {character[][]} board
 * @return {boolean}
 */
var isValidSudoku = function (board) {
  let seenGrid = new Array(9).fill(false);
  const seenCol = Array.from({ length: 9 }, () => new Array(9).fill(false));
  const seenRow = Array.from({ length: 9 }, () => new Array(9).fill(false));

  for (let rowOffset = 0; rowOffset < 9; rowOffset += 3) {
    for (let colOffset = 0; colOffset < 9; colOffset += 3) {
      for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
          if (board[i + rowOffset][j + colOffset] === ".") continue;

          const current =
            board[i + rowOffset][j + colOffset].charCodeAt(0) -
            "0".charCodeAt(0) -
            1;

          if (seenGrid[current]) return false;
          seenGrid[current] = true;

          if (seenRow[i + rowOffset][current]) return false;
          seenRow[i + rowOffset][current] = true;

          if (seenCol[j + colOffset][current]) return false;
          seenCol[j + colOffset][current] = true;
        }
      }
      seenGrid.fill(false);
    }
  }

  return true;
};
