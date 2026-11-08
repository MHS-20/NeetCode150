#include <stdbool.h>
#include <string.h>

static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static bool dfs(char **board, int rows, int cols, const char *word, int len,
                int idx, int row, int col) {
  char ch = word[idx];
  if (ch != board[row][col])
    return false;

  if (idx == len - 1)
    return true;

  board[row][col] = '#';
  for (int d = 0; d < 4; d++) {
    int nr = row + dirs[d][0], nc = col + dirs[d][1];

    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
      continue;

    if (dfs(board, rows, cols, word, len, idx + 1, nr, nc)) {
      board[row][col] = ch; // restore before returning, so the board is unchanged
      return true;
    }
  }

  board[row][col] = ch;
  return false;
}

bool exist(char **board, int boardSize, int *boardColSize, char *word) {
  int len = strlen(word);
  for (int r = 0; r < boardSize; r++)
    for (int c = 0; c < boardColSize[0]; c++)
      if (dfs(board, boardSize, boardColSize[0], word, len, 0, r, c))
        return true;
  return false;
}
