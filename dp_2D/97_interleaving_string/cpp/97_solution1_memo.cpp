#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  bool f(int i, int j, string &s1, string &s2, string &s3,
         vector<vector<int>> &dp) {
    if (i == s1.size() && j == s2.size())
      return true; // used everything
    if (dp[i][j] != -1)
      return dp[i][j];

    int k = i + j; // position in s3
    bool res = false;
    if (i < s1.size() && s1[i] == s3[k])
      res = f(i + 1, j, s1, s2, s3, dp); // take from s1
    if (!res && j < s2.size() && s2[j] == s3[k])
      res = f(i, j + 1, s1, s2, s3, dp); // take from s2

    return dp[i][j] = res;
  }

  bool isInterleave(string s1, string s2, string s3) {
    int n = s1.size(), m = s2.size();
    if (n + m != s3.size())
      return false;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return f(0, 0, s1, s2, s3, dp);
  }
};
