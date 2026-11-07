#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool exist(vector<vector<char>> &board, const string &word) {
    for (int r = 0; r < (int)board.size(); r++)
      for (int c = 0; c < (int)board[0].size(); c++)
        if (dfs(board, word, 0, r, c))
          return true;
    return false;
  }

  bool dfs(vector<vector<char>> &board, const string &word, int idx, int row,
           int col) {
    int constexpr dict[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    char ch = word[idx];
    if (ch != board[row][col])
      return false;

    if (idx == word.size() - 1)
      return true;

    board[row][col] = '#';
    for (auto [dr, dc] : dict) {
      int nr = row + dr, nc = col + dc;

      if (nr < 0 || nr >= board.size() || nc < 0 || nc >= board[0].size())
        continue;

      if (dfs(board, word, idx + 1, nr, nc))
        return true;
    }

    board[row][col] = ch;
    return false;
  }
};
