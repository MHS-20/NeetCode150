#include <algorithm>
#include <array>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>>
        pq; // {elev, r, c}
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    pq.push({grid[0][0], 0, 0});
    visited[0][0] = true;
    int t = 0;

    while (!pq.empty()) {
      auto [elev, r, c] = pq.top();
      pq.pop();
      t = max(t, elev);
      if (r == n - 1 && c == n - 1)
        return t;

      for (auto &d : dirs) {
        int nr = r + d[0], nc = c + d[1];
        if (nr < 0 || nc < 0 || nr >= n || nc >= n || visited[nr][nc])
          continue;
        visited[nr][nc] = true;
        pq.push({grid[nr][nc], nr, nc});
      }
    }
    return -1;
  }
};
