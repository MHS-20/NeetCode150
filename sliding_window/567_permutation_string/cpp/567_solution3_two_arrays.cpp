#include <array>
#include <string>
using namespace std;

class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    int k = s1.size();
    array<int, 26> freq{}, wfreq{};

    for (char ch : s1)
      freq[ch - 'a']++;

    int matches = 0;
    for (int i = 0; i < 26; i++)
      if (freq[i] == wfreq[i])
        matches++; // empty window: letters absent from s1 already match

    auto update = [&](char ch, int delta) {
      int c = ch - 'a';
      if (wfreq[c] == freq[c])
        matches--;

      wfreq[c] += delta;
      if (wfreq[c] == freq[c])
        matches++;
    };

    for (int right = 0; right < s2.size(); right++) {
      update(s2[right], +1); // char enters

      if (right >= k)
        update(s2[right - k], -1); // char leaves
      if (matches == 26)
        return true;
    }
    return false;
  }
};
