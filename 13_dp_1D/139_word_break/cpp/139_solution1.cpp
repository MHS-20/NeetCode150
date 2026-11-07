#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  bool wordBreak(string s, vector<string> &wordDict) {
    int n = s.size();
    unordered_set<string> words(wordDict.begin(), wordDict.end());
    vector<bool> dp(n + 1, false);
    dp[0] = true; // empty prefix is segmentable

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < i; j++) {
        if (dp[j] && words.count(s.substr(j, i - j))) {
          dp[i] = true;
          break; // one valid split is enough
        }
      }
    }
    return dp[n];
  }
};
