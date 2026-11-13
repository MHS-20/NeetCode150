#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int n = s.size(), bestLen = 0, bestStart = 0;
    vector<vector<bool>> memo(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++)
      memo[i][i] = true;

    for (int i = n - 1; i >= 0; i--) {
      for (int j = i; j < n; j++) {
        if (s[i] == s[j] && (j - i < 2 || memo[i + 1][j - 1])) {
          memo[i][j] = true;
          if (j - i + 1 > bestLen) {
            bestLen = j - i + 1;
            bestStart = i;
          }
        }
      }
    }

    return s.substr(bestStart, bestLen);
  }
};
