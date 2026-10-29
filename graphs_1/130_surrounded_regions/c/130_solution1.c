static const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

static void dfs(char **board, int r, int c, int rows, int cols) {
  if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != 'O')
    return;
  board[r][c] = '.';
  for (int d = 0; d < 4; d++)
    dfs(board, r + dirs[d][0], c + dirs[d][1], rows, cols);
}

void solve(char **board, int boardSize, int *boardColSize) {
  int rows = boardSize, cols = boardColSize[0];

  // 1. mark border-connected 'O's as safe
  for (int i = 0; i < rows; i++) {
    dfs(board, i, 0, rows, cols);
    dfs(board, i, cols - 1, rows, cols);
  }
  for (int j = 0; j < cols; j++) {
    dfs(board, 0, j, rows, cols);
    dfs(board, rows - 1, j, rows, cols);
  }

  // 2. capture leftover 'O's, restore safe ones
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      if (board[i][j] == 'O')
        board[i][j] = 'X';
      else if (board[i][j] == '.')
        board[i][j] = 'O';
    }
}
