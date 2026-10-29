#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  int orangesRotting(vector<vector<int>> &grid) {
    static constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int, int>> q;
    int fresh = 0;

    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++) {
        if (grid[i][j] == 2)
          q.push({i, j});
        else if (grid[i][j] == 1)
          fresh++;
      }

    int minutes = 0;
    while (!q.empty() && fresh > 0) {
      int sz = q.size();
      minutes++;
      for (int k = 0; k < sz; k++) {
        auto [r, c] = q.front();
        q.pop();
        for (auto [dr, dc] : dirs) {
          int nr = r + dr, nc = c + dc;
          if (nr < 0 || nc < 0 || nr >= rows || nc >= cols)
            continue;
          if (grid[nr][nc] != 1)
            continue;

          grid[nr][nc] = 2;
          fresh--;
          q.push({nr, nc});
        }
      }
    }
    return fresh == 0 ? minutes : -1;
  }
};
