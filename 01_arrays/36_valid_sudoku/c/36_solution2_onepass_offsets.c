#include <stdbool.h>
#include <string.h>

bool isValidSudoku(char **board, int boardSize, int *boardColSize) {
  bool seenGrid[9] = {false};
  bool seenCol[9][9] = {{false}};
  bool seenRow[9][9] = {{false}};

  for (int rowOffset = 0; rowOffset < 9; rowOffset += 3) {
    for (int colOffset = 0; colOffset < 9; colOffset += 3) {
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (board[i + rowOffset][j + colOffset] == '.')
            continue;

          int current = board[i + rowOffset][j + colOffset] - '0' - 1;

          if (seenGrid[current])
            return false;
          seenGrid[current] = true;

          if (seenRow[i + rowOffset][current])
            return false;
          seenRow[i + rowOffset][current] = true;

          if (seenCol[j + colOffset][current])
            return false;
          seenCol[j + colOffset][current] = true;
        }
      }
      memset(seenGrid, false, sizeof(seenGrid));
    }
  }

  return true;
}
