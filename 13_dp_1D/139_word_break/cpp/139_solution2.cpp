#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  bool wordBreak(string s, vector<string> &wordDict) {
    int n = s.size();
    unordered_set<string> words(wordDict.begin(), wordDict.end());

    int maxLen = 0;
    for (auto &w : wordDict)
      maxLen = max(maxLen, (int)w.size());

    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int i = 1; i <= n; i++) {
      // A piece longer than maxLen can't be a word, so start j no earlier than
      // i - maxLen
      for (int j = max(0, i - maxLen); j < i; j++) {
        if (dp[j] && words.count(s.substr(j, i - j))) {
          dp[i] = true;
          break;
        }
      }
    }
    return dp[n];
  }
};
