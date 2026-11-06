#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int bestStart = 0, bestLen = 1;

    // Every single character is a palindrome
    for (int i = 0; i < n; i++)
      dp[i][i] = true;

    // Fill by increasing substring length
    for (int len = 2; len <= n; len++) {
      for (int i = 0; i + len - 1 < n; i++) {
        int j = i + len - 1;

        if (s[i] == s[j] && (len == 2 || dp[i + 1][j - 1])) {
          dp[i][j] = true;
          if (len > bestLen) {
            bestStart = i;
            bestLen = len;
          }
        }
      }
    }
    return s.substr(bestStart, bestLen);
  }
};
