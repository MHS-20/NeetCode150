#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int f(int i, int j, string &s, string &t, vector<vector<int>> &dp) {
    if (j == 0)
      return 1; // t fully matched
    if (i == 0)
      return 0; // s ran out first
    if (dp[i][j] != -1)
      return dp[i][j];

    long long ways = f(i - 1, j, s, t, dp); // skip s[i-1]
    if (s[i - 1] == t[j - 1])
      ways += f(i - 1, j - 1, s, t, dp); // pick it

    return dp[i][j] = (int)ways;
  }

  int numDistinct(string s, string t) {
    int n = s.size(), m = t.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return f(n, m, s, t, dp);
  }
};
