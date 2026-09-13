#include <vector>
using namespace std;

class Solution {
public:
  bool isValidSudoku(vector<vector<char>> &board) {
    bool seen[9] = {};

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.')
          continue;
        int current = board[i][j] - '0' - 1;
        if (seen[current]) {
          return false;
        } else {
          seen[current] = true;
        }
      } // cols
      fill(begin(seen), end(seen), false);
    } // rows

    for (int j = 0; j < 9; j++) {
      for (int i = 0; i < 9; i++) {
        if (board[i][j] == '.')
          continue;
        int current = board[i][j] - '0' - 1;
        if (seen[current]) {
          return false;
        } else {
          seen[current] = true;
        }
      } // rows
      fill(begin(seen), end(seen), false);
    } // cols

    for (int rowOffset = 0; rowOffset < 9; rowOffset += 3) {
      for (int colOffset = 0; colOffset < 9; colOffset += 3) {

        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (board[i + rowOffset][j + colOffset] == '.')
              continue;
            int current = board[i + rowOffset][j + colOffset] - '0' - 1;
            if (seen[current]) {
              return false;
            } else {
              seen[current] = true;
            }
          }
        } // grid 3x3
        fill(begin(seen), end(seen), false);
      }
    } // all grids

    return true;
  }
};
