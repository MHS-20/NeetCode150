#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool isMatch(string s, string p) {
    int n = s.size(), m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;

    auto matches = [&](int i, int j) {
      return p[j - 1] == '.' || s[i - 1] == p[j - 1];
    };

    for (int i = 0; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (p[j - 1] == '*') {
          dp[i][j] = dp[i][j - 2]; // zero copies
          if (i > 0 && matches(i, j - 1))
            dp[i][j] = dp[i][j] || dp[i - 1][j]; // one more copy
        } else {
          dp[i][j] = i > 0 && matches(i, j) && dp[i - 1][j - 1];
        }
      }
    }
    return dp[n][m];
  }
};
