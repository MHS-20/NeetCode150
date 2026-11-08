#include <string>
#include <unordered_map>
using namespace std;
class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    int k = s1.size();
    unordered_map<char, int> freq, wfreq;
    for (char c : s1)
      freq[c]++;

    int need = freq.size();
    int matches = 0;

    auto update = [&](char c, int delta) {
      auto it = freq.find(c);
      if (it == freq.end())
        return;

      int target = it->second;
      if (wfreq[c] == target)
        matches--;

      wfreq[c] += delta;
      if (wfreq[c] == target)
        matches++;
    };

    for (int right = 0; right < s2.size(); right++) {
      update(s2[right], +1); // char enters

      if (right >= k)
        update(s2[right - k], -1); // char leaves

      if (matches == need)
        return true;
    }
    return false;
  }
};
