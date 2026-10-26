#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
    rows = heights.size();
    cols = heights[0].size();
    vector<vector<bool>> pacific(rows, vector<bool>(cols, false));
    vector<vector<bool>> atlantic(rows, vector<bool>(cols, false));

    for (int i = 0; i < rows; i++) {
      dfs(heights, pacific, i, 0, INT_MIN);
      dfs(heights, atlantic, i, cols - 1, INT_MIN);
    }
    for (int j = 0; j < cols; j++) {
      dfs(heights, pacific, 0, j, INT_MIN);
      dfs(heights, atlantic, rows - 1, j, INT_MIN);
    }

    vector<vector<int>> result;
    for (int i = 0; i < rows; i++)
      for (int j = 0; j < cols; j++)
        if (pacific[i][j] && atlantic[i][j])
          result.push_back({i, j});
    return result;
  }

private:
  int rows, cols;
  static constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  void dfs(vector<vector<int>> &heights, vector<vector<bool>> &ocean, int r,
           int c, int prevHeight) {
    if (r < 0 || c < 0 || r >= rows || c >= cols)
      return;
    if (ocean[r][c] || heights[r][c] < prevHeight)
      return;

    ocean[r][c] = true;
    for (auto [dr, dc] : dirs)
      dfs(heights, ocean, r + dr, c + dc, heights[r][c]);
  }
};
