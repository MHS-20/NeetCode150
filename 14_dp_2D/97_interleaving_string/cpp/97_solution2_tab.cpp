#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    int n = s1.size(), m = s2.size();
    if (n + m != s3.size())
      return false;

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true; // empty + empty = empty

    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        if (i == 0 && j == 0)
          continue;
        int k = i + j - 1; // last char of s3 prefix
        bool fromS1 = i > 0 && dp[i - 1][j] && s1[i - 1] == s3[k];
        bool fromS2 = j > 0 && dp[i][j - 1] && s2[j - 1] == s3[k];
        dp[i][j] = fromS1 || fromS2;
      }
    }
    return dp[n][m];
  }
};
