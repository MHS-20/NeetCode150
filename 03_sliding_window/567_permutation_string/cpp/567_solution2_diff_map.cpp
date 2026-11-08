#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    int k = s1.size();
    unordered_map<char, int> diff;
    int mismatched = 0;

    auto update = [&](char c, int delta) {
      if (diff[c] == 0)
        mismatched++;
      diff[c] += delta;
      if (diff[c] == 0)
        mismatched--;
    };

    for (char c : s1)
      update(c, -1);

    for (int right = 0; right < s2.size(); right++) {
      update(s2[right], +1); // char enters
      if (right >= k)
        update(s2[right - k], -1); // char leaves
      if (mismatched == 0)
        return true;
    }
    return false;
  }
};
