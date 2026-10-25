#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    if (grid.empty())
      return 0;
    int rows = grid.size(), cols = grid[0].size();
    int count = 0;
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        if (grid[i][j] == '1') {
          sink(grid, i, j, rows, cols);
          count++;
        }
    return count;
  }

private:
  static constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  void sink(vector<vector<char>> &grid, int r, int c, int rows, int cols) {
    queue<pair<int, int>> q;
    q.push({r, c});
    grid[r][c] = '0';
    while (!q.empty()) {
      auto [cr, cc] = q.front();
      q.pop();
      for (auto [dr, dc] : dirs) {
        int nr = cr + dr, nc = cc + dc;
        if (nr >= 0 && nc >= 0 && nr < rows && nc < cols &&
            grid[nr][nc] == '1') {
          grid[nr][nc] = '0';
          q.push({nr, nc});
        }
      }
    }
  }
};
