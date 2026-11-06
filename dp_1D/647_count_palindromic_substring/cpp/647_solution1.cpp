#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int countSubstrings(string s) {
    int n = s.size();
    int count = 0;
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++) {
      dp[i][i] = true;
      count++;
    }

    for (int len = 2; len <= n; len++) {
      for (int i = 0; i + len - 1 < n; i++) {
        int j = i + len - 1;

        if (s[i] == s[j] && (len == 2 || dp[i + 1][j - 1])) {
          dp[i][j] = true;
          count++;
        }
      }
    }

    return count;
  }
};
