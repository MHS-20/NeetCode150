#include <algorithm>
#include <string>

using namespace std;

class Solution {
  // Grow outward from the center (left, right) while the ends match.
  // Returns the length of the palindrome found.
  int expand(const string &s, int left, int right) {
    while (left >= 0 && right < (int)s.size() && s[left] == s[right]) {
      left--;
      right++;
    }
    return right - left - 1;
  }

public:
  string longestPalindrome(string s) {
    int bestStart = 0, bestLen = 0;

    for (int i = 0; i < (int)s.size(); i++) {
      int oddLen = expand(s, i, i); // center on a character: "aba"
      int evenLen =
          expand(s, i, i + 1); // center between two characters: "abba"
      int len = max(oddLen, evenLen);

      if (len > bestLen) {
        bestLen = len;
        bestStart = i - (len - 1) / 2;
      }
    }
    return s.substr(bestStart, bestLen);
  }
};
