#include <array>
#include <climits>
#include <string>
using namespace std;
class Solution {
public:
  string minWindow(string s, string t) {
    array<int, 128> need{};
    for (char c : t)
      need[c]++;
    int missing = t.size();

    int bestStart = 0, bestLen = INT_MAX;
    int left = 0;

    for (int right = 0; right < s.size(); right++) {
      if (need[s[right]]-- > 0)
        missing--; // this char was still needed

      while (missing == 0) { // window is valid: try to shrink
        if (right - left + 1 < bestLen) {
          bestStart = left;
          bestLen = right - left + 1;
        }
        if (++need[s[left]] > 0)
          missing++; // we just removed a needed char
        left++;
      }
    }
    return bestLen == INT_MAX ? "" : s.substr(bestStart, bestLen);
  }
};
