class Solution {
public:
  string longestPalindrome(string s) {
    int n = s.size();
    memo.assign(n, vector<int>(n, -1)); // -1 unknown, 0 no, 1 yes
    int bestStart = 0, bestLen = 0;

    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (j - i + 1 > bestLen && isPal(s, i, j)) {
          bestLen = j - i + 1;
          bestStart = i;
        }
      }
    }
    return s.substr(bestStart, bestLen);
  }

private:
  vector<vector<int>> memo;

  bool isPal(const string &s, int i, int j) {
    if (i >= j)
      return true; // length 0 or 1
    if (memo[i][j] != -1)
      return memo[i][j];
    memo[i][j] = (s[i] == s[j]) && isPal(s, i + 1, j - 1);
    return memo[i][j];
  }
};
