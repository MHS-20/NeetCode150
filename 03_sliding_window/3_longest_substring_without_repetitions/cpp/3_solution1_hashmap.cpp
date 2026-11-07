#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastSeen;
    int maxLen = 0, left = 0;

    for (int right = 0; right < s.size(); right++) {
      char c = s[right];
      if (lastSeen.count(c) && lastSeen[c] >= left) {
        left = lastSeen[c] + 1;
      }
      lastSeen[c] = right;
      maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
  }
};
