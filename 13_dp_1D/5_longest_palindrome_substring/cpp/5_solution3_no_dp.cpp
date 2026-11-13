#include <string>

using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int bestStart = 0, bestLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
      // odd-length palindromes, centered on s[i]
      expand(s, i, i, bestStart, bestLen);
      // even-length palindromes, centered between s[i] and s[i+1]
      expand(s, i, i + 1, bestStart, bestLen);
    }

    return s.substr(bestStart, bestLen);
  }

private:
  void expand(const string &s, int l, int r, int &bestStart, int &bestLen) {
    // bounds first, so s[l] and s[r] are only read when valid
    while (l >= 0 && r < (int)s.size() && s[l] == s[r]) {
      l--;
      r++;
    }
    // pointers overshot by one on each side: palindrome is s[l+1 .. r-1]
    int len = r - l - 1;
    if (len > bestLen) {
      bestLen = len;
      bestStart = l + 1;
    }
  }
};
