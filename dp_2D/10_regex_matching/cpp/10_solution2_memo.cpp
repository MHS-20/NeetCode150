#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool matches(string &s, string &p, int i, int j) { // s[i-1] vs p[j-1]
    return p[j - 1] == '.' || s[i - 1] == p[j - 1];
  }

  bool f(int i, int j, string &s, string &p, vector<vector<int>> &dp) {
    if (j == 0)
      return i == 0; // empty pattern matches only empty s
    if (dp[i][j] != -1)
      return dp[i][j];

    bool res;
    if (p[j - 1] == '*') {
      res = f(i, j - 2, s, p, dp); // zero copies
      if (!res && i > 0 && matches(s, p, i, j - 1))
        res = f(i - 1, j, s, p, dp); // one more copy
    } else {
      res = i > 0 && matches(s, p, i, j) && f(i - 1, j - 1, s, p, dp);
    }
    return dp[i][j] = res;
  }

  bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return f(n, m, s, p, dp);
  }
};
