#include <stdbool.h>

static bool checkAndMark(bool arr[9], int idx) {
  if (arr[idx])
    return false;
  arr[idx] = true;
  return true;
}

bool isValidSudoku(char **board, int boardSize, int *boardColSize) {
  bool seenRows[9][9] = {{false}};
  bool seenCols[9][9] = {{false}};
  bool seenBoxes[9][9] = {{false}};

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == '.')
        continue;

      int current = board[i][j] - '0' - 1;
      int box = (i / 3) * 3 + (j / 3);

      if (!checkAndMark(seenRows[i], current))
        return false;
      if (!checkAndMark(seenCols[j], current))
        return false;
      if (!checkAndMark(seenBoxes[box], current))
        return false;
    }
  }

  return true;
}
