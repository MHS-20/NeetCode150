#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int f(int i, int j, string &a, string &b, vector<vector<int>> &dp) {
    if (i == 0)
      return j; // insert the remaining j chars
    if (j == 0)
      return i; // delete the remaining i chars
    if (dp[i][j] != -1)
      return dp[i][j];

    if (a[i - 1] == b[j - 1])
      return dp[i][j] = f(i - 1, j - 1, a, b, dp); // free match

    int del = f(i - 1, j, a, b, dp);
    int ins = f(i, j - 1, a, b, dp);
    int rep = f(i - 1, j - 1, a, b, dp);
    return dp[i][j] = 1 + min({del, ins, rep});
  }

  int minDistance(string word1, string word2) {
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return f(n, m, word1, word2, dp);
  }
};
