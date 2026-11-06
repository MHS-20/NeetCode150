#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool wordBreak(string s, vector<string> &wordDict) {
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
      for (auto &w : wordDict) {
        int len = w.size();
        // Does word w end exactly at position i?
        if (len <= i && dp[i - len] && s.compare(i - len, len, w) == 0) {
          dp[i] = true;
          break;
        }
      }
    }
    return dp[n];
  }
};
