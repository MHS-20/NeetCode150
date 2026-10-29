#include <vector>

using namespace std;

class Solution {
public:
  void solve(vector<vector<char>> &board) {
    rows = board.size();
    cols = board[0].size();

    // 1. mark border-connected 'O's as safe
    for (int i = 0; i < rows; i++) {
      dfs(board, i, 0);
      dfs(board, i, cols - 1);
    }
    for (int j = 0; j < cols; j++) {
      dfs(board, 0, j);
      dfs(board, rows - 1, j);
    }

    // 2. capture leftover 'O's, restore safe ones
    for (auto &row : board)
      for (char &cell : row) {
        if (cell == 'O')
          cell = 'X';
        else if (cell == '.')
          cell = 'O';
      }
  }

private:
  int rows, cols;
  static constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  void dfs(vector<vector<char>> &board, int r, int c) {
    if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != 'O')
      return;
    board[r][c] = '.';
    for (auto [dr, dc] : dirs)
      dfs(board, r + dr, c + dc);
  }
};
