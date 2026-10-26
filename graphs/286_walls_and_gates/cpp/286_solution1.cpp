#include <climits>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  void islandsAndTreasure(vector<vector<int>> &grid) {
    rows = grid.size();
    cols = grid[0].size();
    queue<pair<int, int>> q;

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        if (grid[i][j] == 0)
          q.push({i, j});

    while (!q.empty()) {
      auto [r, c] = q.front();
      q.pop();
      for (auto [dr, dc] : dirs) {
        int nr = r + dr, nc = c + dc;
        if (nr < 0 || nc < 0 || nr >= rows || nc >= cols)
          continue;
        if (grid[nr][nc] != INT_MAX)
          continue;

        grid[nr][nc] = grid[r][c] + 1;
        q.push({nr, nc});
      }
    }
  }

private:
  int rows, cols;
  static constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
};
