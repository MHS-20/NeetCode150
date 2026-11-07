#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int maxAreaOfIsland(vector<vector<int>> &grid) {
    if (grid.empty())
      return 0;

    int mx = 0, count = 0;
    int rows = grid.size(), cols = grid[0].size();

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        if (grid[i][j] == 1) {
          count = 0;
          sink(grid, i, j, rows, cols, count);
          mx = max(count, mx);
        }
    return mx;
  }

private:
  static constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  void sink(vector<vector<int>> &grid, int r, int c, int rows, int cols,
            int &count) {
    if (r < 0 || c < 0 || r >= rows || c >= cols || grid[r][c] != 1)
      return;
    grid[r][c] = 0;
    count++;
    for (auto [dr, dc] : dirs)
      sink(grid, r + dr, c + dc, rows, cols, count);
  }
};
