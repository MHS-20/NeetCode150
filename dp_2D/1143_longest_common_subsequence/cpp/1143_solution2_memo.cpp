#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int solve(int i, int j, string &a, string &b, vector<vector<int>> &dp) {
    if (i == 0 || j == 0)
      return 0; // one string is empty
    if (dp[i][j] != -1)
      return dp[i][j];

    if (a[i - 1] == b[j - 1])
      return dp[i][j] = 1 + solve(i - 1, j - 1, a, b, dp);
    return dp[i][j] = max(solve(i - 1, j, a, b, dp), solve(i, j - 1, a, b, dp));
  }

  int longestCommonSubsequence(string text1, string text2) {
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return solve(n, m, text1, text2, dp);
  }
};
