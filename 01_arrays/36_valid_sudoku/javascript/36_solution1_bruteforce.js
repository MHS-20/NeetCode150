/**
 * @param {character[][]} board
 * @return {boolean}
 */
var isValidSudoku = function (board) {
  let seen = new Array(9).fill(false);

  for (let i = 0; i < 9; i++) {
    for (let j = 0; j < 9; j++) {
      if (board[i][j] === ".") continue;
      const current = board[i][j].charCodeAt(0) - "0".charCodeAt(0) - 1;
      if (seen[current]) return false;
      seen[current] = true;
    }
    seen.fill(false);
  }

  for (let j = 0; j < 9; j++) {
    for (let i = 0; i < 9; i++) {
      if (board[i][j] === ".") continue;
      const current = board[i][j].charCodeAt(0) - "0".charCodeAt(0) - 1;
      if (seen[current]) return false;
      seen[current] = true;
    }
    seen.fill(false);
  }

  for (let rowOffset = 0; rowOffset < 9; rowOffset += 3) {
    for (let colOffset = 0; colOffset < 9; colOffset += 3) {
      for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
          if (board[i + rowOffset][j + colOffset] === ".") continue;
          const current =
            board[i + rowOffset][j + colOffset].charCodeAt(0) -
            "0".charCodeAt(0) -
            1;
          if (seen[current]) return false;
          seen[current] = true;
        }
      }
      seen.fill(false);
    }
  }

  return true;
};
