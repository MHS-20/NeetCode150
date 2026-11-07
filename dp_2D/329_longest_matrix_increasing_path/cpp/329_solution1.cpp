#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int m, n;
  int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  int dfs(int i, int j, vector<vector<int>> &matrix, vector<vector<int>> &dp) {
    if (dp[i][j] != 0)
      return dp[i][j]; // already computed

    int best = 1; // the cell alone
    for (auto &d : dirs) {
      int ni = i + d[0], nj = j + d[1];
      if (ni >= 0 && ni < m && nj >= 0 && nj < n &&
          matrix[ni][nj] > matrix[i][j]) {
        best = max(best, 1 + dfs(ni, nj, matrix, dp));
      }
    }
    return dp[i][j] = best;
  }

  int longestIncreasingPath(vector<vector<int>> &matrix) {
    m = matrix.size();
    n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));

    int res = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        res = max(res, dfs(i, j, matrix, dp));
    return res;
  }
};
