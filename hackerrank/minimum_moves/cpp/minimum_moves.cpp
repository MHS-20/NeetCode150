#include <bits/stdc++.h>
using namespace std;

// Minimum Moves
//
// In a grid-based maze, each cell is either empty (0) or contains an obstacle
// (1).
//
// HackerMan must navigate from cell (0, 0) to cell (n-1, m-1) with a jump
// parameter k, allowing these moves:
//   - Right: (i, j) -> (i, j+x) where 1 <= x <= k
//   - Down:  (i, j) -> (i+x, j) where 1 <= x <= k
//   - Left:  (i, j) -> (i, j-x) where 1 <= x <= k
//   - Up:    (i, j) -> (i-x, j) where 1 <= x <= k
//
// For any move, all cells in the path must be obstacle-free and within
// maze boundaries.
//
// Determine the minimum number of moves required to reach the destination,
// or return -1 if it is impossible.
//
// Example
// Consider n = 2, m = 2, jump parameter k = 2,
// and maze = [[0, 0], [1, 0]].
//
// The maze looks like this:
//   [0 0]
//   [1 0]
//
// Expected answer: 2  ((0,0) -> (0,1) -> (1,1))

int minimumMoves(vector<vector<int>> maze, int k) {
  int n = maze.size(), m = maze[0].size();
  if (maze[0][0] == 1 || maze[n - 1][m - 1] == 1)
    return -1;

  const int INF = INT_MAX;
  vector<vector<int>> dist(n, vector<int>(m, INF));
  dist[0][0] = 0;
  queue<pair<int, int>> q;
  q.push({0, 0});
  int di[4] = {0, 1, 0, -1}; // right, down, left, up
  int dj[4] = {1, 0, -1, 0};

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();
    if (i == n - 1 && j == m - 1)
      return dist[i][j];
    int d = dist[i][j] + 1;
    for (int dir = 0; dir < 4; dir++) {
      for (int x = 1; x <= k; x++) {
        int ni = i + di[dir] * x, nj = j + dj[dir] * x;
        // out of bounds or obstacle: can't jump through it
        if (ni < 0 || ni >= n || nj < 0 || nj >= m || maze[ni][nj] == 1)
          break;
        // reached earlier with fewer moves: it covers the rest
        if (dist[ni][nj] < d)
          break;
        // already at this level: skip, but keep sliding
        if (dist[ni][nj] == d)
          continue;
        dist[ni][nj] = d;
        q.push({ni, nj});
      }
    }
  }
  return -1;
}

int main() {
  vector<vector<int>> maze = {{0, 0}, {1, 0}};
  cout << minimumMoves(maze, 2) << endl; // 2
  return 0;
}
