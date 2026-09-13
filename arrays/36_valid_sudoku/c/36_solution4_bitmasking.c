#include <stdbool.h>

static bool checkAndMark(int *mask, int idx) {
  if ((*mask & (1 << idx)) != 0)
    return false;
  *mask |= (1 << idx);
  return true;
}

bool isValidSudoku(char **board, int boardSize, int *boardColSize) {
  int seenRows[9] = {0};
  int seenCols[9] = {0};
  int seenBoxes[9] = {0};

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == '.')
        continue;

      int current = board[i][j] - '0' - 1;
      int box = (i / 3) * 3 + (j / 3);

      if (!checkAndMark(&seenRows[i], current))
        return false;
      if (!checkAndMark(&seenCols[j], current))
        return false;
      if (!checkAndMark(&seenBoxes[box], current))
        return false;
    }
  }

  return true;
}
