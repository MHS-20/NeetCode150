#include <vector>
using namespace std;

class Solution {
public:
  bool isValidSudoku(vector<vector<char>> &board) {
    int seenRows[9] = {0};
    int seenCols[9] = {0};
    int seenBoxes[9] = {0};

    auto checkAndMark = [](int &mask, int idx) {
      if ((mask & (1 << idx)) != 0)
        return false;
      mask = mask | (1 << idx);
      return true;
    };

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
};
