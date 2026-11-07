#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
  int n;
  vector<vector<int>> *g;

  bool canReach(int t) {
    auto &grid = *g;
    if (grid[0][0] > t)
      return false;
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    queue<pair<int, int>> q;
    q.push({0, 0});
    visited[0][0] = true;
    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty()) {
      auto [r, c] = q.front();
      q.pop();
      if (r == n - 1 && c == n - 1)
        return true;
      for (auto &d : dirs) {
        int nr = r + d[0], nc = c + d[1];
        if (nr < 0 || nc < 0 || nr >= n || nc >= n)
          continue;
        if (visited[nr][nc] || grid[nr][nc] > t)
          continue;
        visited[nr][nc] = true;
        q.push({nr, nc});
      }
    }
    return false;
  }

public:
  int swimInWater(vector<vector<int>> &grid) {
    n = grid.size();
    g = &grid;
    int lo = 0, hi = n * n - 1;
    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      if (canReach(mid))
        hi = mid; // works: try lower
      else
        lo = mid + 1; // fails: need more water
    }
    return lo;
  }
};
