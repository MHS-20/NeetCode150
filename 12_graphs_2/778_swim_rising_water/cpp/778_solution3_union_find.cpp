#include <numeric>
#include <utility>
#include <vector>

using namespace std;

class Solution {
  vector<int> parent, rnk;

  int find(int x) {
    while (parent[x] != x) {
      parent[x] = parent[parent[x]]; // path halving
      x = parent[x];
    }
    return x;
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return;
    if (rnk[a] < rnk[b])
      swap(a, b);
    parent[b] = a;
    if (rnk[a] == rnk[b])
      rnk[a]++;
  }

public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();
    parent.resize(n * n);
    rnk.assign(n * n, 0);
    iota(parent.begin(), parent.end(), 0);

    // pos[v] = cell index holding elevation v
    vector<int> pos(n * n);
    for (int r = 0; r < n; r++)
      for (int c = 0; c < n; c++)
        pos[grid[r][c]] = r * n + c;

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (int t = 0; t < n * n; t++) {
      int r = pos[t] / n, c = pos[t] % n; // this cell becomes submerged
      for (auto &d : dirs) {
        int nr = r + d[0], nc = c + d[1];
        if (nr < 0 || nc < 0 || nr >= n || nc >= n)
          continue;
        if (grid[nr][nc] <= t) // neighbor already submerged
          unite(r * n + c, nr * n + nc);
      }
      if (find(0) == find(n * n - 1))
        return t;
    }
    return -1;
  }
};
