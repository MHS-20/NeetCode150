#include <string>
#include <vector>

using namespace std;

class Solution {
  vector<bool> cols, diag1, diag2;

public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    cols.assign(n, false);
    diag1.assign(2 * n - 1, false);
    diag2.assign(2 * n - 1, false);
    backtrack(n, 0, board, result);
    return result;
  }

private:
  void backtrack(int n, int row, vector<string> &board,
                 vector<vector<string>> &result) {
    if (row == n) {
      result.push_back(board);
      return;
    }

    for (int col = 0; col < n; col++) {
      int d1 = row + col;         // "/" diagonal
      int d2 = row - col + n - 1; // "\" diagonal, shifted
      if (cols[col] || diag1[d1] || diag2[d2])
        continue;

      board[row][col] = 'Q';
      cols[col] = diag1[d1] = diag2[d2] = true;

      backtrack(n, row + 1, board, result);

      board[row][col] = '.';
      cols[col] = diag1[d1] = diag2[d2] = false;
    }
  }
};
