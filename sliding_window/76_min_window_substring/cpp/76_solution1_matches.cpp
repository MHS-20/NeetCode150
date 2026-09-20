#include <climits>
#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
  string minWindow(string s, string t) {
    unordered_map<char, int> tfreq;
    unordered_map<char, int> wfreq;
    unordered_map<char, int> widxs;

    int left = 0;
    int matches = 0;
    int minLen = INT_MAX;
    string substr = "";

    for (char c : t)
      tfreq[c]++;

    for (int right = 0; right < s.size(); right++) {
      char c = s[right];
      wfreq[c]++;

      if (tfreq.count(c) && wfreq[c] == tfreq[c]) {
        matches++;
      }

      if (matches == tfreq.size()) {
        while (tfreq.count(s[left]) == 0 || wfreq[s[left]] > tfreq[s[left]]) {
          wfreq[s[left]]--;
          left++;

          if (left >= right || left >= s.size() - 1)
            break;
        }
        int curLen = right - left + 1;
        if (curLen < minLen) {
          substr = s.substr(left, curLen);
          minLen = curLen;
        }
      }
    }

    return substr;
  }
};
