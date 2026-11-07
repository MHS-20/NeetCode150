#include <vector>
using namespace std;

class Solution {
public:
  bool isValidSudoku(vector<vector<char>> &board) {
    bool seenGrid[9] = {};
    bool seenCol[9][9] = {{}};
    bool seenRow[9][9] = {{}};

    for (int rowOffset = 0; rowOffset < 9; rowOffset += 3) {
      for (int colOffset = 0; colOffset < 9; colOffset += 3) {

        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            if (board[i + rowOffset][j + colOffset] == '.')
              continue;

            int current = board[i + rowOffset][j + colOffset] - '0' - 1;

            // current grid
            if (seenGrid[current]) {
              return false;
            } else {
              seenGrid[current] = true;
            }

            // row
            if (seenRow[i + rowOffset][current]) {
              return false;
            } else {
              seenRow[i + rowOffset][current] = true;
            }

            // cols
            if (seenCol[j + colOffset][current]) {
              return false;
            } else {
              seenCol[j + colOffset][current] = true;
            }
          }
        } // grid 3x3
        fill(begin(seenGrid), end(seenGrid), false);
      }
    }

    return true;
  }
};
